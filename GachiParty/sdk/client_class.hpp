#pragma once
#include "client_networkable.hpp"
#include "netvars.hpp"
typedef c_client_networkable* (*CreateClientClassFn)(int entnum, int serialNum);
typedef c_client_networkable* (*CreateEventFn)();
class ClientClass
{
public:
	ClientClass(const char* pNetworkName, CreateClientClassFn createFn, CreateEventFn createEventFn, RecvTable* pRecvTable)
	{
		m_pNetworkName = pNetworkName;
		m_pCreateFn = createFn;
		m_pCreateEventFn = createEventFn;
		m_pRecvTable = pRecvTable;

		// Link it in   EDITED 10.07.2021
		/*m_pNext = g_pClientClassHead;*/
		/*g_pClientClassHead = this;*/
	}

	const char* GetName()
	{
		return m_pNetworkName;
	}

public:
	CreateClientClassFn		m_pCreateFn;
	CreateEventFn			m_pCreateEventFn;	// Only called for event objects.
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int						m_ClassID;	// Managed by the engine.
};
