/*
 * Aspire Hearthstone
 * Copyright (C) 2008 - 2009 AspireDev <http://www.aspiredev.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StdAfx.h"
GameObject::GameObject(uint64 guid)
{
	m_objectTypeId = TYPEID_GAMEOBJECT;
	m_valuesCount = GAMEOBJECT_END;
	m_uint32Values = _fields;
	memset(m_uint32Values, 0,(GAMEOBJECT_END)*sizeof(uint32));
	m_updateMask.SetCount(GAMEOBJECT_END);
	SetUInt32Value( OBJECT_FIELD_TYPE,TYPE_GAMEOBJECT|TYPE_OBJECT);
	SetUInt64Value( OBJECT_FIELD_GUID,guid);
	m_wowGuid.Init(GetGUID());
 
	SetFloatValue( OBJECT_FIELD_SCALE_X, 1);//info->Size  );

	SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_ANIMPROGRESS, 100);

	counter=0;//not needed at all but to prevent errors that var was not inited, can be removed in release

	bannerslot = bannerauraslot = -1;

	m_summonedGo = false;
	invisible = false;
	invisibilityFlag = INVIS_FLAG_NORMAL;
	spell = 0;
	m_summoner = NULLUNIT;
	charges = -1;
	m_ritualcaster = 0;
	m_ritualtarget = 0;
	m_ritualmembers = NULL;
	m_ritualspell = 0;
	m_rotation = 0;

	m_quests = NULL;
	pInfo = NULL;
	myScript = NULL;
	m_spawn = 0;
	m_deleted = false;
	mines_remaining = 1;
	m_respawnCell=NULL;
	m_battleground = NULLBATTLEGROUND;
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
	Object::Init();
}

void GameObject::Destructor()
{
	sEventMgr.RemoveEvents(shared_from_this());
	if(m_ritualmembers)
		delete[] m_ritualmembers;

	uint32 guid = GetUInt32Value(OBJECT_FIELD_CREATED_BY);
	if(guid)
	{
		PlayerPointer plr = objmgr.GetPlayer(guid);
		if(plr && plr->GetSummonedObject() == object_shared_from_this() )
			plr->SetSummonedObject(NULLOBJ);

		if(plr == m_summoner)
			m_summoner = NULLUNIT;
	}

	if(m_respawnCell!=NULL)
		m_respawnCell->_respawnObjects.erase( TO_OBJECT(shared_from_this()) );

	if (m_summonedGo && m_summoner)
		for(int i = 0; i < 4; i++)
			if (m_summoner->m_ObjectSlots[i] == GetUIdFromGUID())
				m_summoner->m_ObjectSlots[i] = 0;

	if( m_battleground != NULL )
	{
		if( m_battleground->GetType() == BATTLEGROUND_ARATHI_BASIN )
		{
			if( bannerslot >= 0 && TO_ARATHIBASIN(m_battleground)->m_controlPoints[bannerslot] == gob_shared_from_this() )
				TO_ARATHIBASIN(m_battleground)->m_controlPoints[bannerslot] = NULLGOB;

			if( bannerauraslot >= 0 && TO_ARATHIBASIN(m_battleground)->m_controlPointAuras[bannerauraslot] == gob_shared_from_this() )
				TO_ARATHIBASIN(m_battleground)->m_controlPointAuras[bannerauraslot] = NULLGOB;
		}
		m_battleground = NULLBATTLEGROUND;
	}

	Object::Destructor();
}

bool GameObject::CreateFromProto(uint32 entry,uint32 mapid, float x, float y, float z, float ang, float orientation1, float orientation2, float orientation3, float orientation4)
{
	pInfo= GameObjectNameStorage.LookupEntry(entry);
	if(!pInfo)
		return false;

	Object::_Create( mapid, x, y, z, ang );
	SetUInt32Value( OBJECT_FIELD_ENTRY, entry );

	SetPosition(x, y, z, orientation1);

	SetFloatValue(GAMEOBJECT_PARENTROTATION_1, ang);
    /*SetFloatValue(GAMEOBJECT_PARENTROTATION_2, orientation2);
    SetFloatValue(GAMEOBJECT_PARENTROTATION_3, orientation3);*/
	UpdateRotation();

	SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, 1);
	SetUInt32Value( GAMEOBJECT_DISPLAYID, pInfo->DisplayID );
	SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPE_ID, pInfo->Type);
   
	InitAI();

	return true;
}

void GameObject::TrapSearchTarget()
{
	Update(100);
}

void GameObject::Update(uint32 p_time)
{
	if(m_event_Instanceid != m_instanceId)
	{
		event_Relocate();
		return;
	}

	if(!IsInWorld())
		return;

	if(m_deleted)
		return;

	if(spell && (GetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE) == 1))
	{
		if(checkrate > 1)
		{
			if(counter++%checkrate)
				return;
		}
		ObjectSet::iterator itr = GetInRangeSetBegin();
		ObjectSet::iterator it2 = itr;
		ObjectSet::iterator iend = GetInRangeSetEnd();
		UnitPointer pUnit;
		float dist;
		for(; it2 != iend;)
		{
			itr = it2;
			++it2;
			dist = GetDistanceSq((*itr));
			if( (*itr) != m_summoner && (*itr)->IsUnit() && dist <= range)
			{
				pUnit = TO_UNIT(*itr);

				if(m_summonedGo)
				{
					if(!m_summoner)
					{
						ExpireAndDelete();
						return;
					}
					if(!isAttackable(m_summoner,pUnit))continue;
				}
				
				SpellPointer sp= SpellPointer (new Spell(obj_shared_from_this(),spell,true,NULLAURA));
				SpellCastTargets tgt((*itr)->GetGUID());
				tgt.m_destX = GetPositionX();
				tgt.m_destY = GetPositionY();
				tgt.m_destZ = GetPositionZ();
				sp->prepare(&tgt);
				if(pInfo->Type == 6)
				{
					if(m_summoner != NULL)
						m_summoner->HandleProc(PROC_ON_TRAP_TRIGGER, pUnit, spell);
				} 

				if(m_summonedGo)
				{
					ExpireAndDelete();
					return;
				}

				if(spell->EffectImplicitTargetA[0] == 16 ||
					spell->EffectImplicitTargetB[0] == 16)
					return;	 // on area dont continue.
			}
		}
	}
}

void GameObject::Spawn( MapMgrPointer m)
{
	PushToWorld(m);	
	CALL_GO_SCRIPT_EVENT(gob_shared_from_this(), OnSpawn)();
}

void GameObject::Despawn(uint32 time)
{
	if(!IsInWorld())
		return;

	//This is for go get deleted while looting
	if( m_spawn != NULL )
	{
		SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_STATE, m_spawn->state);
		SetUInt32Value(GAMEOBJECT_FLAGS, m_spawn->flags);
	}

	CALL_GO_SCRIPT_EVENT(gob_shared_from_this(), OnDespawn)();

	if(time)
	{
		/* Get our originiating mapcell */
		MapCell * pCell = m_mapCell;
		ASSERT(pCell);
		pCell->_respawnObjects.insert( obj_shared_from_this() );
		sEventMgr.RemoveEvents(shared_from_this());
		sEventMgr.AddEvent(m_mapMgr, &MapMgr::EventRespawnGameObject, gob_shared_from_this(), pCell, EVENT_GAMEOBJECT_ITEM_SPAWN, time, 1, 0);
		Object::RemoveFromWorld(false);
		m_respawnCell=pCell;
	}
	else
	{
		Object::RemoveFromWorld(false);
		ExpireAndDelete();
	}
}

void GameObject::SaveToDB()
{
	std::stringstream ss;
	ss << "REPLACE INTO gameobject_spawns VALUES("
		<< ((m_spawn == NULL) ? 0 : m_spawn->id) << ","
		<< GetEntry() << ","
		<< GetMapId() << ","
		<< GetPositionX() << ","
		<< GetPositionY() << ","
		<< GetPositionZ() << ","
		<< GetOrientation() << ","
		<< GetUInt64Value(GAMEOBJECT_ROTATION) << ","
		<< GetFloatValue(GAMEOBJECT_PARENTROTATION) << ","
		<< GetFloatValue(GAMEOBJECT_PARENTROTATION_2) << ","
		<< GetFloatValue(GAMEOBJECT_PARENTROTATION_3) << ","
		<< ( GetByte(GAMEOBJECT_BYTES_1, 0)? 1 : 0 ) << ","
		<< GetUInt32Value(GAMEOBJECT_FLAGS) << ","
		<< GetUInt32Value(GAMEOBJECT_FACTION) << ","
		<< GetFloatValue(OBJECT_FIELD_SCALE_X) << ","
		<< m_phaseMode <<")";
	WorldDatabase.Execute(ss.str().c_str());
}

void GameObject::SaveToFile(std::stringstream & name)
{
/*	std::stringstream ss;
	if (!m_sqlid)
		m_sqlid = objmgr.GenerateLowGuid(HIGHGUID_GAMEOBJECT);

	 ss.rdbuf()->str("");
	 ss << "INSERT INTO gameobjects VALUES ( "
		<< m_sqlid << ", "
		<< m_position.x << ", "
		<< m_position.y << ", "
		<< m_position.z << ", "
		<< m_position.o << ", "
		<< GetZoneId() << ", "
		<< GetMapId() << ", '";

	for( uint32 index = 0; index < m_valuesCount; index ++ )
		ss << GetUInt32Value(index) << " ";

	ss << "', ";
	ss << GetEntry() << ", 0, 0)"; 

	FILE * OutFile;

	OutFile = fopen(name.str().c_str(), "wb");
	if (!OutFile) return;
	fwrite(ss.str().c_str(),1,ss.str().size(),OutFile);
	fclose(OutFile);
*/
}

void GameObject::InitAI()
{	
	if(pInfo == NULL)
		return;
	
	// this fixes those fuckers in booty bay
	if(pInfo->SpellFocus == 0 &&
		pInfo->sound1 == 0 &&
		pInfo->sound2 == 0 &&
		pInfo->sound3 != 0 &&
		pInfo->sound5 != 3 &&
		pInfo->sound9 == 1)
		return;

/*	if(pInfo->DisplayID == 1027)//Shaman Shrine
	{
		if(pInfo->ID != 177964 || pInfo->ID != 153556)
		{
			Deactivate
			SetUInt32Value(GAMEOBJECT_DYNAMIC, 0);
		}
	}*/


	uint32 spellid = 0;
	switch(pInfo->Type)
	{
		case GAMEOBJECT_TYPE_TRAP:
		{	
			spellid = pInfo->sound3;
		}break;
		case GAMEOBJECT_TYPE_SPELL_FOCUS://redirect to properties of another go
		{
			uint32 new_entry = pInfo->sound2;
			if(new_entry)
			{
				pInfo = GameObjectNameStorage.LookupEntry( new_entry );
				if(pInfo == NULL)
				{
					Log.Warning("GameObject","Redirected gameobject %u doesn't seem to exists in database, skipping",new_entry);
					return;
				}
				if(pInfo->sound3)
					spellid = pInfo->sound3;
			}
		}break;
		case GAMEOBJECT_TYPE_RITUAL:
		{	
			m_ritualmembers = new uint32[pInfo->SpellFocus];
			memset(m_ritualmembers,0,sizeof(uint32)*pInfo->SpellFocus);
		}break;
		case GAMEOBJECT_TYPE_CHEST:
 		{
			Lock *pLock = dbcLock.LookupEntry(GetInfo()->SpellFocus);
			if(pLock)
			{
				for(uint32 i=0; i < 5; i++)
				{
					if(pLock->locktype[i])
					{
						if(pLock->locktype[i] == 2) //locktype;
						{
							//herbalism and mining;
							if(pLock->lockmisc[i] == LOCKTYPE_MINING || pLock->lockmisc[i] == LOCKTYPE_HERBALISM)
							{
								CalcMineRemaining(true);
							}
						}
					}
				}
			}
		}break;
	}
	//Null out gossip_script here, will be set with sScriptMgr.register_go_gossip_script (if any).
	pInfo->gossip_script = NULL;
	myScript = sScriptMgr.CreateAIScriptClassForGameObject(GetEntry(), gob_shared_from_this());

	// hackfix for bad spell in BWL
	if(!spellid || spellid == 22247)
		return;

	SpellEntry *sp= dbcSpell.LookupEntry(spellid);
	if(!sp)
	{
		spell = NULL;
		return;
	}
	else
	{
		spell = sp;
	}
	//ok got valid spell that will be casted on target when it comes close enough
	//get the range for that 
	
	float r = 0;

	for(uint32 i=0;i<3;i++)
	{
		if(sp->Effect[i])
		{
			float t = GetRadius(dbcSpellRadius.LookupEntry(sp->EffectRadiusIndex[i]));
			if(t > r)
				r = t;
		}
	}

	if(r < 0.1)//no range
		r = GetMaxRange(dbcSpellRange.LookupEntry(sp->rangeIndex));

	range = r*r;//square to make code faster
	checkrate = 20;//once in 2 seconds
	
}

bool GameObject::Load(GOSpawn *spawn)
{
	if(!CreateFromProto(spawn->entry,0,spawn->x,spawn->y,spawn->z,spawn->facing,spawn->orientation1,spawn->orientation2,spawn->orientation3,spawn->orientation4))
		return false;

	m_phaseMode = spawn->phase;
	m_spawn = spawn;
	SetUInt32Value(GAMEOBJECT_FLAGS,spawn->flags);
//	SetUInt32Value(GAMEOBJECT_LEVEL,spawn->level);
	SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, spawn->state);
	if(spawn->faction)
	{
		SetUInt32Value(GAMEOBJECT_FACTION,spawn->faction);
		m_faction = dbcFactionTemplate.LookupEntry(spawn->faction);
		if(m_faction)
			m_factionDBC = dbcFaction.LookupEntry(m_faction->Faction);
	}
	SetFloatValue(OBJECT_FIELD_SCALE_X,spawn->scale);

	if( spawn->flags & GO_FLAG_IN_USE || spawn->flags & GO_FLAG_LOCKED )
		SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_ANIMPROGRESS, 100);

	CALL_GO_SCRIPT_EVENT(gob_shared_from_this(), OnCreate)();

	_LoadQuests();
	return true;
}

void GameObject::DeleteFromDB()
{
	if( m_spawn != NULL )
		WorldDatabase.Execute("DELETE FROM gameobject_spawns WHERE id=%u", m_spawn->id);
}

void GameObject::EventCloseDoor()
{
	SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_STATE, 0);
}

void GameObject::UseFishingNode(PlayerPointer player)
{
	sEventMgr.RemoveEvents( shared_from_this() );
	if( GetUInt32Value( GAMEOBJECT_FLAGS ) != 32 ) // Clicking on the bobber before something is hooked
	{
		player->GetSession()->OutPacket( SMSG_FISH_NOT_HOOKED );
		EndFishing( player, true );
		return;
	}
	
	/* Unused code: sAreaStore.LookupEntry(GetMapMgr()->GetAreaID(GetPositionX(),GetPositionY()))->ZoneId*/
	uint32 zone = player->GetAreaID();
	if( zone == 0 ) // If the player's area ID is 0, use the zone ID instead
		zone = player->GetZoneId();

	FishingZoneEntry *entry = FishingZoneStorage.LookupEntry( zone );
	if( entry == NULL ) // No fishing information found for area or zone, log an error, and end fishing
	{
		OUT_DEBUG( "ERROR: Fishing zone information for zone %d not found!", zone );
		EndFishing( player, true );
		return;
	}
	uint32 maxskill = entry->MaxSkill;
//	uint32 minskill = entry->MaxSkill;
	uint32 minskill = entry->MinSkill;

	if( player->_GetSkillLineCurrent( SKILL_FISHING, false ) < maxskill )	
		player->_AdvanceSkillLine( SKILL_FISHING, float2int32( 1.0f * sWorld.getRate( RATE_SKILLRATE ) ) );

	// Open loot on success, otherwise FISH_ESCAPED.
	if( Rand(((player->_GetSkillLineCurrent( SKILL_FISHING, true ) - minskill) * 100) / maxskill) )
	{
		lootmgr.FillFishingLoot( &m_loot, zone );
		player->SendLoot( GetGUID(), LOOT_FISHING );
		EndFishing( player, false );
	}
	else // Failed
	{
		player->GetSession()->OutPacket( SMSG_FISH_ESCAPED );
		EndFishing( player, true );
	}

}

void GameObject::EndFishing(PlayerPointer player, bool abort )
{
	SpellPointer spell = player->GetCurrentSpell();
	
	if(spell)
	{
		if(abort)   // abort becouse of a reason
		{
			//FIXME: here 'failed' should appear over progress bar
			spell->SendChannelUpdate(0);
			//spell->cancel();
			spell->finish();
		}
		else		// spell ended
		{
			spell->SendChannelUpdate(0);
			spell->finish();
		}
	}

	if(!abort)
		sEventMgr.AddEvent(gob_shared_from_this(), &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_EXPIRE, 10000, 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	else
		ExpireAndDelete();
}

void GameObject::FishHooked(PlayerPointer player)
{
	WorldPacket  data(12);
	data.Initialize(SMSG_GAMEOBJECT_CUSTOM_ANIM); 
	data << GetGUID();
	data << (uint32)(0); // value < 4
	player->GetSession()->SendPacket(&data);
	//SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_STATE, 0);
	//BuildFieldUpdatePacket(player, GAMEOBJECT_FLAGS, 32);
	SetUInt32Value(GAMEOBJECT_FLAGS, 32);
 }

/////////////
/// Quests

void GameObject::AddQuest(QuestRelation *Q)
{
	m_quests->push_back(Q);
}

void GameObject::DeleteQuest(QuestRelation *Q)
{
	list<QuestRelation *>::iterator it;
	for( it = m_quests->begin(); it != m_quests->end(); ++it )
	{
		if( ( (*it)->type == Q->type ) && ( (*it)->qst == Q->qst ) )
		{
			delete (*it);
			m_quests->erase(it);
			break;
		}
	}
}

Quest* GameObject::FindQuest(uint32 quest_id, uint8 quest_relation)
{   
	list< QuestRelation* >::iterator it;
	for( it = m_quests->begin(); it != m_quests->end(); ++it )
	{
		QuestRelation* ptr = (*it);
		if( ( ptr->qst->id == quest_id ) && ( ptr->type & quest_relation ) )
		{
			return ptr->qst;
		}
	}
	return NULL;
}

uint16 GameObject::GetQuestRelation(uint32 quest_id)
{
	uint16 quest_relation = 0;
	list< QuestRelation* >::iterator it;
	for( it = m_quests->begin(); it != m_quests->end(); ++it )
	{
		if( (*it) != NULL && (*it)->qst->id == quest_id )
		{
			quest_relation |= (*it)->type;
		}
	}
	return quest_relation;
}

uint32 GameObject::NumOfQuests()
{
	return (uint32)m_quests->size();
}

void GameObject::_LoadQuests()
{
	sQuestMgr.LoadGOQuests(gob_shared_from_this());

	// set state for involved quest objects
	if( pInfo && pInfo->InvolvedQuestIds )
	{
		SetUInt32Value(GAMEOBJECT_DYNAMIC, 0);
		SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_STATE, 0);
		SetUInt32Value(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
	}
}

/////////////////
// Summoned Go's
//guardians are temporary spawn that will inherit master faction and will folow them. Apart from that they have their own mind
UnitPointer GameObject::CreateTemporaryGuardian(uint32 guardian_entry,uint32 duration,float angle, UnitPointer u_caster)
{
	CreatureProto * proto = CreatureProtoStorage.LookupEntry(guardian_entry);
	CreatureInfo * info = CreatureNameStorage.LookupEntry(guardian_entry);
	if(!proto || !info)
	{
		OUT_DEBUG("Warning : Missing summon creature template %u !",guardian_entry);
		return NULLUNIT;
	}
	uint32 lvl = u_caster->getLevel();
	float m_fallowAngle=angle;
	float x = GetPositionX()+(3*(cosf(m_fallowAngle+GetOrientation())));
	float y = GetPositionY()+(3*(sinf(m_fallowAngle+GetOrientation())));
	float z = GetPositionZ();
	CreaturePointer p = GetMapMgr()->CreateCreature(guardian_entry);
	p->SetInstanceID(GetMapMgr()->GetInstanceID());
	p->Load(proto, x, y, z, 0.0f);

	if (lvl != 0)
	{
		/* MANA */
		p->SetPowerType(POWER_TYPE_MANA);
		p->SetUInt32Value(UNIT_FIELD_MAXPOWER1,p->GetUInt32Value(UNIT_FIELD_MAXPOWER1)+28+10*lvl);
		p->SetUInt32Value(UNIT_FIELD_POWER1,p->GetUInt32Value(UNIT_FIELD_POWER1)+28+10*lvl);
		/* HEALTH */
		p->SetUInt32Value(UNIT_FIELD_MAXHEALTH,p->GetUInt32Value(UNIT_FIELD_MAXHEALTH)+28+30*lvl);
		p->SetUInt32Value(UNIT_FIELD_HEALTH,p->GetUInt32Value(UNIT_FIELD_HEALTH)+28+30*lvl);
		/* LEVEL */
		p->SetUInt32Value(UNIT_FIELD_LEVEL, lvl);
	}

	p->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, GetGUID());
    p->SetUInt64Value(UNIT_FIELD_CREATEDBY, GetGUID());
    p->SetZoneId(GetZoneId());
	p->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE,u_caster->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
	p->_setFaction();

	p->GetAIInterface()->Init(p,AITYPE_PET,MOVEMENTTYPE_NONE,u_caster);
	p->GetAIInterface()->SetUnitToFollow(unit_shared_from_this());
	p->GetAIInterface()->SetUnitToFollowAngle(m_fallowAngle);
	p->GetAIInterface()->SetFollowDistance(3.0f);

	p->PushToWorld(GetMapMgr());

	sEventMgr.AddEvent(p, &Creature::SummonExpire, EVENT_SUMMON_EXPIRE, duration, 1,0);

	return p;

}
void GameObject::_Expire()
{
	sEventMgr.RemoveEvents(shared_from_this());
	if(IsInWorld())
		RemoveFromWorld(true);

	//sEventMgr.AddEvent(World::getSingletonPtr(), &World::DeleteObject, object_shared_from_this(), EVENT_DELETE_TIMER, 1000, 1);
	//delete this; you don't get to do that.
	Destructor();
}

void GameObject::ExpireAndDelete()
{
	if(m_deleted)
		return;

	m_deleted = true;
	
	/* remove any events */
	sEventMgr.RemoveEvents(shared_from_this());
	sEventMgr.AddEvent(gob_shared_from_this(), &GameObject::_Expire, EVENT_GAMEOBJECT_EXPIRE, 1, 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
}

void GameObject::CallScriptUpdate()
{
	ASSERT(myScript);
	myScript->AIUpdate();
}

void GameObject::OnPushToWorld()
{
	Object::OnPushToWorld();
}

void GameObject::OnRemoveInRangeObject(ObjectPointer pObj)
{
	Object::OnRemoveInRangeObject(pObj);
	if(m_summonedGo && m_summoner == pObj)
	{
		for(int i = 0; i < 4; i++)
			if (m_summoner->m_ObjectSlots[i] == GetUIdFromGUID())
				m_summoner->m_ObjectSlots[i] = 0;

		m_summoner = NULLUNIT;
		ExpireAndDelete();
	}
}

void GameObject::RemoveFromWorld(bool free_guid)
{
	WorldPacket data(SMSG_GAMEOBJECT_DESPAWN_ANIM, 8);
	data << GetGUID();
	SendMessageToSet(&data,true);

	sEventMgr.RemoveEvents(shared_from_this(), EVENT_GAMEOBJECT_TRAP_SEARCH_TARGET);
	Object::RemoveFromWorld(free_guid);
}

uint32 GameObject::GetGOReqSkill()  
{
	if(GetEntry() == 180215) return 300;

	if(GetInfo() == NULL)
		return 0;

	Lock *lock = dbcLock.LookupEntry( GetInfo()->SpellFocus );
	if(!lock) return 0;
	for(uint32 i=0;i<5;i++)
		if(lock->locktype[i] == 2 && lock->minlockskill[i])
		{
			return lock->minlockskill[i];
		}
	return 0;
}

void GameObject::GenerateLoot()
{

}

// Convert from radians to blizz rotation system
void GameObject::UpdateRotation()
{
	m_rotation = 0;
	uint32 max = (1 << 20) - 2;	// first 2 fields are 21 bit long. so max positive value is this
	for(uint32 i = 0; i < 3; i++)
	{
		if(i == 2)
			max = (1 << 21) - 2;	// last field is 1 bit wider than first 2
		float rad = GetFloatValue(GAMEOBJECT_ROTATION_01 + i);
		if (rad < 0)
		{
			rad = float(2 * M_PI) + rad;
		}
		if (rad > (float)M_PI)
		{
			rad = -sinf(rad/2.0f);
		} else
		{
			rad = sinf(rad/2.0f);
		}
		m_rotation |= uint64(float2int32(max * rad)) << (21 * i);
	}
}

//	custom functions for scripting
void GameObject::SetState(uint8 state)
{
	SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, state);
}

uint8 GameObject::GetState()
{
	return GetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE);
}
