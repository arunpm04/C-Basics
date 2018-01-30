#include <stdio.h>
#include <stdlib.h>

typedef enum {
	FALSE,
	TRUE
} BOOL;

/* Valid Event List */
typedef enum {
	EVENT_X,
	EVENT_Y,
	EVENT_Z,
	EVENT_MAX
} Event_t;

/* Valid State List */
typedef enum {
	STATE_X,
	STATE_Y,
	STATE_Z,
	STATE_MAX
} State_t;

struct state_transition
{
	State_t (*function)(Event_t *new_event);
};

/* Action Handlers */
State_t Action_EventX_StateX(Event_t *new_event)
{
	printf("%s\n", __func__);
	*new_event = EVENT_X;
	return STATE_Y;
}

State_t Action_EventX_StateY(Event_t *new_event)
{
	printf("%s\n", __func__);
	*new_event = EVENT_X;
	return STATE_Z;
}

State_t Action_EventX_StateZ(Event_t *new_event)
{
	printf("%s\n", __func__);
	*new_event = EVENT_Y;
	return STATE_X;
}

State_t Action_EventY_StateX(Event_t *new_event)
{
	printf("%s\n", __func__);
	*new_event = EVENT_Y;
	return STATE_Y;
}

State_t Action_EventY_StateY(Event_t *new_event)
{
	printf("%s\n", __func__);
	*new_event = EVENT_Y;
	return STATE_Z;
}

State_t Action_EventY_StateZ(Event_t *new_event)
{
	printf("%s\n", __func__);
	*new_event = EVENT_Z;
	return STATE_X;
}

State_t Action_EventZ_StateX(Event_t *new_event)
{
	printf("%s\n", __func__);
	*new_event = EVENT_Z;
	return STATE_Y;
}

State_t Action_EventZ_StateY(Event_t *new_event)
{
	printf("%s\n", __func__);
	*new_event = EVENT_Z;
	return STATE_Z;
}

State_t Action_Dummy(Event_t *new_event)
{
	printf("%s\n", __func__);
	return STATE_Z;
}

State_t Action_EventZ_StateZ(Event_t *new_event)
{
	printf("%s\n", __func__);
	*new_event = STATE_MAX;
	return STATE_MAX;
}

/* Event - State Action Handler Table */
struct state_transition stateTrans[EVENT_MAX][STATE_MAX] =
{
	{Action_EventX_StateX, Action_EventX_StateY, Action_EventX_StateZ},
	{Action_EventY_StateX, Action_Dummy, Action_EventY_StateZ},
	{Action_EventZ_StateX, Action_EventZ_StateY, Action_EventZ_StateZ},
};

/* Action Map Routine. */
BOOL ProcessEvent(State_t *new_state, Event_t *new_event)
{
	/* Check State Validity */
	if (*new_state >= STATE_MAX || *new_event >= EVENT_MAX)
		return FALSE;
	/* Take Action */
	*new_state = stateTrans[*new_event][*new_state].function(new_event);
	return TRUE;
}

/* Simple event generator. */
Event_t CaptureEvent(void)
{
	int i;
	printf("Simple Event Generator\nSelect respective option\n");
	printf("1. Event X\n");
	printf("2. Event Y\n");
	printf("3. Event Z\n");
	printf("4. Event Invalid\n");
	printf("0. Exit\n");
	scanf("%d", &i);
	if (i == 0)
		exit(0);
	if (i > 9 || i < 0)
	return (i-1);
}

/* Event Capture & Validation Routine. */
BOOL GetEvent(Event_t *new_event)
{
	Event_t event = CaptureEvent();
	if ((event < EVENT_MAX) && (event >= EVENT_X)) {
		/* Valid Event */
		*new_event = event;
		return TRUE;
	}
	printf("Invalid Event:%x\n", event);
	return FALSE;
}

int main(int argc,char *argv[])
{
	State_t new_state = STATE_X;
	Event_t new_event = EVENT_X;
	while(1) {
		/* Get event. */
		if (GetEvent(&new_event) == TRUE)
			ProcessEvent(&new_state, &new_event);
	}
}
