#pragma once
#include <cstddef>


class i_game_event
{
public:
	virtual ~i_game_event() {};
	virtual const char* get_name() const = 0;	// get event name
	virtual bool  is_reliable() const = 0; // if event handled reliable
	virtual bool  is_local() const = 0; // if event is never networked
	virtual bool  is_empty(const char* keyName = NULL) const = 0; // check if data field exists
	// Data access
	virtual bool  get_bool(const char* keyName = NULL, bool defaultValue = false) const = 0;
	virtual int   get_int(const char* keyName = NULL, int defaultValue = 0) const = 0;
	virtual unsigned __int64 get_uint_64(const char* keyName = NULL, unsigned __int64 defaultValue = 0) const = 0;
	virtual float get_float(const char* keyName = NULL, float defaultValue = 0.0f) const = 0;
	virtual const char* get_string(const char* keyName = NULL, const char* defaultValue = "") const = 0;
	virtual const wchar_t* get_wstring(const char* keyName = NULL, const wchar_t* defaultValue = L"") const = 0;
	virtual const void* get_ptr(const char* keyName = NULL) const = 0;	// LOCAL only
	virtual void set_bool(const char* keyName, bool value) = 0;
	virtual void set_int(const char* keyName, int value) = 0;
	virtual void set_uint64(const char* keyName, unsigned __int64 value) = 0;
	virtual void set_float(const char* keyName, float value) = 0;
	virtual void set_string(const char* keyName, const char* value) = 0;
	virtual void set_wstring(const char* keyName, const wchar_t* value) = 0;
	virtual void set_ptr(const char* keyName, const void* value) = 0;	// LOCAL only

	// returns true if iteration aborted normally, false if it was aborted by the visitor callback
	virtual bool ForEventData(void* event) const = 0;//IgameEventVisitor2*
};

#define EVENT_DEBUG_ID_INIT			42
#define EVENT_DEBUG_ID_SHUTDOWN		13