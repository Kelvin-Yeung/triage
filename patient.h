// maximal accepted length of the patient's name
extern const int MAX_NAME_LEN;

// A record for a patient in the emergency room
struct patient;

// patient_read() reads information for one patient from input. Format is:
//   <priority:int> <name:string>
//   * priority must be between 1 and 9 (both inclusive); a lower value
//     indicates higher priority, e.g., 3 is of higher priority than 8
//   * name must not contain any spaces and not be longer than MAX_NAME_LEN
// effects: allocates heap memory [client must call patient_destroy]
// time:    O(1)
struct patient *patient_read(void);

// patient_clone(p) returns a clone of *p.
// effects: allocates heap memory [client must call patient_destroy]
// time:    O(1)
struct patient *patient_clone(const struct patient *p);

// patient_destroy(p) releases all resources used by *p.
// effects: invalidates *p
// time:    O(1)
void patient_destroy(struct patient *p);

// patient_priority(p) returns the priority of patient *p.
// time:    O(1)
int patient_priority(const struct patient *p);

// patient_print(p) prints the *p to output.
// effects: produces output
// time:    O(1)
void patient_print(const struct patient *p);