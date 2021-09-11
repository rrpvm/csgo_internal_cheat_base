#pragma once
#include "i_client_engine.h"
#define CLIENT_DLL_INTERFACE_VERSION		"VClient018"
class i_base_client_dll {
public:
	/*Õ≈ Œ––≈ “Õ€≈ »Õƒ≈ —€!*/
	virtual void			create_move(
		int sequence_number,			// sequence_number of this cmd
		float input_sample_frametime,	// Frametime for mouse input sampling
		bool active) = 0;				// True if the player is active (not paused)

	virtual void			frame_stage_notify(ClientFrameStage_t curStage) = 0;//36
	ClientClass* get_all_classes() {
		return vmt_load::call_function<8, ClientClass*>(this);
	};
};