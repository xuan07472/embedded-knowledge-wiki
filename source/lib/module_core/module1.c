//#include "module.h"

//static MSTATE module_process(MODULE_T *module, int idx)
//{
//	load_buf = sysbuf_alloc(SYSBUF_GROUP_DATBUFS);
//	psysbuf_t buf = SessionBufferPop(punit->session, SESSION_DEVGROUP_BASIC);
//	sbf = SessionBufferPush(punit->session_audio, SESSION_DEVGROUP_BASIC,load_buf);

//	if (SessionBufferTopNum(punit->session_audio,
//			SESSION_DEVGROUP_BASIC) > 1)
//		session->state = SSTATE_RUNNING;
//}

//static int module_control(MODULE_T *module)
//{
	
//}

//static int module_stop(MODULE_T *module)
//{
//	if (punit->load_buf) {
//		sysbuf_free(punit->load_buf);
//		punit->load_buf = NULL;
//	}
	
//	SessionBufferDeInit(session);
//}

//static int module_start(MODULE_T *module)
//{
//	punit->load_buf = sysbuf_alloc(SYSBUF_GROUP_DATBUFS);
//	if (punit->load_buf == NULL) {
//		punit->session_audio = NULL;
//		return -ENOMEM;
//	}

//	SessionBufferClean(session, SESSION_DEVGROUP_BASIC);
//}

//static void module_destroy(MODULE_T *module)
//{
//	SessionBufferDeInit(session);
//}

//static void module_create(MODULE_T *module)
//{

//}

//MODULE_T g_module_1 {
	
//}
