#pragma once

namespace Internal
{
	// Storage for addresses
	class Addresses
	{
	public:
		bool Init();

		// WSOCK32 addresses
		HMODULE	  wsock32;

		// Student addresses
		uintptr_t	student_alert_bad_word;
		uintptr_t	student_clear_student_desktop;
		uintptr_t	student_close_lsk_web_svr;
		uintptr_t	student_deinit_check_network_connections;
		uintptr_t	student_enum_chrome32_windows_proc;
		uintptr_t	student_find_and_close_window_with_name;
		uintptr_t	student_get_registry_value;
		uintptr_t	student_get_student_state;
		uintptr_t	student_has_display_changed;
		uintptr_t	student_new_desktop_detected;
		uintptr_t	student_post_data;
		uintptr_t	student_select_input_desktop;
		uintptr_t	student_sent_packet_to;
		uintptr_t	student_set_registry_value;
		uintptr_t	student_set_teacher_sspi_state;

	};
	extern Addresses addresses;
}