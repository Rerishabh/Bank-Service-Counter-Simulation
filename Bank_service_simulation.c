#include <stdio.h>

#define MAX 100
#define COUNTERS 2   

typedef struct {
    int token;
    int serviceTime;
} Customer;

Customer queue[MAX];
int front = 0, rear = 0;

int counterBusy[COUNTERS];
int counterToken[COUNTERS];
int counterTime[COUNTERS];


int isEmpty() { return front == rear; }
int isFull() { return rear == MAX; }

void enqueue(int token, int time) {
    if (!isFull()) {
        queue[rear].token = token;
        queue[rear].serviceTime = time;
        rear++;
    }
}

Customer dequeue() {
    Customer c = {-1, -1};
    if (!isEmpty()) c = queue[front++];
    return c;
}

int main() {
    int choice, token, t, timeStep = 0;

    for (int i = 0; i < COUNTERS; i++)
        counterBusy[i] = 0;

    while (1) {
        printf("\n1. Add Customer\n2. Simulate 1 Time Unit\n3. Exit\nEnter: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter Token Number: ");
            scanf("%d", &token);
            printf("Enter Service Time: ");
            scanf("%d", &t);
            enqueue(token, t);
            printf("Customer %d added to waiting queue.\n", token);
        }

        else if (choice == 2) {
            timeStep++;
            printf("\n--- TIME STEP %d ---\n", timeStep);

            
            for (int i = 0; i < COUNTERS; i++) {
                if (counterBusy[i]) {
                    counterTime[i]--;
                    if (counterTime[i] == 0) {
                        printf("Counter %d finished serving Token %d\n",
                               i + 1, counterToken[i]);
                        counterBusy[i] = 0;
                    }
                }
            }

            
            for (int i = 0; i < COUNTERS; i++) {
                if (!counterBusy[i] && !isEmpty()) {
                    Customer c = dequeue();
                    counterBusy[i] = 1;
                    counterToken[i] = c.token;
                    counterTime[i] = c.serviceTime;
                    printf("Counter %d started serving Token %d (Time: %d)\n",
                           i + 1, c.token, c.serviceTime);
                }
            }
        }

        else if (choice == 3) {
            printf("Simulation Ended.\n");
            break;
        }
    }

    return 0;
}
