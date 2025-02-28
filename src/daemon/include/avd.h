#ifndef AVD_H
#define AVD_H

#include <linux/types.h>

#define MAX_ALERT_MSG 256

typedef struct {
    pid_t pid;
    char executable_name[256];
    char alert_msg[MAX_ALERT_MSG];
} alert_t;

void send_alert(alert_t *alert);
void handle_alerts(void);
void init_daemon(void);
void cleanup_daemon(void);

#endif // AVD_H