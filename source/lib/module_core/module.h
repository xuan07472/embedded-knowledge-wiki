
typedef enum
{
	STATE_NULL = 0,
	STATE_CREATE,
	STATE_PROCESS,
	STATE_IDLE,
	STATE_PAUSE,
	STATE_DESTROY,
}MSTATE;

typedef struct MODULE {
	slists_group_t buffer_group;
} MODULE_T