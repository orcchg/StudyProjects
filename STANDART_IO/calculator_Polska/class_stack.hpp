#include <cstdlib>

class Stack {
			 int* m_data;
			 int m_size;
			 int m_ptr;
	
	public:
			Stack(int size) {
				m_size = size;
				m_data = (int*)malloc(m_size*sizeof(int));
				m_ptr = 0;
			}
			~Stack() {
				free(m_data);
			}
			
			int pop(void) {
				if(m_ptr)
					return m_data[--m_ptr];
				else
					return -999; //Stack is empty; Error!
			}
			
			void push(int a) {
				if(m_ptr >= m_size-1) {//Stack is full;
					m_size = 10 + 2*m_size;
					m_data = (int*)realloc(m_data,m_size*sizeof(int));
				}
				m_data[m_ptr++] = a;
			}
			
			bool empty() {
				return (m_ptr == 0);
			}
};