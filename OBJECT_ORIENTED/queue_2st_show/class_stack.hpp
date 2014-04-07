#include <cstdlib>

class Stack {
			 int* m_data;
			 int m_size;
			 int m_ptr;
	
	public:
			int top;
			
			Stack(int size) {
				m_size = size;
				m_data = (int*)malloc(m_size*sizeof(int));
				m_ptr = 0;
				top = 0;
			}
			~Stack() {
				free(m_data);
			}
			
			int pop(void) {
				if(m_ptr) {
					top = m_ptr-1;
					return m_data[--m_ptr];
				}
				else {
					top = 0;
					return -999; //Stack is empty; Error!
				}	
			}
			
			void push(int a) {
				if(m_ptr >= m_size-1) {//Stack is full;
					m_size = 10 + 2*m_size;
					m_data = (int*)realloc(m_data,m_size*sizeof(int));
				}
				top = m_ptr;
				m_data[m_ptr++] = a;
			}
			
			bool empty() {
				return (m_ptr == 0);
			}
};

class Queue {

	public: 	
			Stack s1;
			Stack s2;
	
			Queue(int size):s1(size),s2(size)
			{}

			void enqueue(int a)
			{	
				s1.push(a);
			}

			int dequeue()
			{	
				if(s1.top == 0 && s2.top == 0){
					return -999;
				}
	
				while(s1.top != 0) {
					s2.push(s1.pop());
				}	
		
				return s2.pop();
			}
};			