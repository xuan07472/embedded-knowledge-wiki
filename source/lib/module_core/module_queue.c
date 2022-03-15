/* 只能在module架构的模块内使用 */


psysbuf_t (struct SESSION *session, int idx)
{
	psysbuf_t buf = NULL;
	session_buflist_t *sbl;
	if (session == NULL || idx < 0 || idx >= SESSION_MAX_DEVGROUP)
		return NULL;
	sbl = (session_buflist_t *)slists_get(&(session->buffer_group),idx);
	if (sbl != NULL)
		buf = SessionSbSwitchFree(sbl);
	return buf;
}

void SessionBufferClean(struct SESSION *session, int idx)
{
	psysbuf_t buf = NULL;
	if (session == NULL || idx < 0 || idx >= SESSION_MAX_DEVGROUP)
		return;
	do {
		buf = SessionBufferPop(session, idx);
		if (buf) {
			sysbuf_free(buf);
		}
	} while (buf != NULL);
}

void SessionBufferDeInit(struct SESSION *session)
{
	int i;
	if (session == NULL)
		return;
	for (i=0; i<SESSION_MAX_DEVGROUP; i++) {
		SessionBufferClean(session, i);
	}
	slists_group_init(&(session->buffer_group));
}