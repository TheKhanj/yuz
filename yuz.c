enum state_t {
	PS_SHUTDOWN = 0,
	PS_STARTED,
	PS_LOADED,
	PS_READY,
	PS_CRASHED
};

typedef void *config_t;

typedef struct {
	enum state_t state;
	config_t config;
} process_t;

void process_init(process_t *p);
// TODO: is this really needed? if malloc is called yes it is.
void process_deinit(process_t *p);
void process_start(process_t *p);
void process_load(process_t *p);
void process_prepare(process_t *p);
void process_stop(process_t *p);
void process_force_stop(process_t *p);

typedef struct {
	process_t *p;
} monitor_t;

void monitor_start(monitor_t *m);
void monitor_stop(monitor_t *m);

