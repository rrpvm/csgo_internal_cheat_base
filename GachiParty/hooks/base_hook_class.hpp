#pragma once
#include "vmt.hpp"
class i_base_hook {
public:
	virtual ~i_base_hook() {};
	vmt& getVMT() { return vmft; };
	void unhook() { vmft.split(); };
	virtual void init() {};
protected:
	vmt vmft;
};