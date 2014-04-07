#include <cstdlib>

class Queue {
			 int* m_data;
			 int m_size;
			 int m_tail;
			 int m_head;
	
	public:
			Queue(int size) {
				m_size = size;
				m_data = (int*)malloc(m_size * sizeof(int));
				m_tail = 0;
				m_head = 0;
			}
			~Queue() {
				free(m_data);
			}
			
			int dequeue(void) {
				if(m_head != m_tail)
					return m_data[m_head++];
				else
					return -999;
			}
					
			void enqueue(int a) {
				if(m_tail >= m_size-1) {
					m_size = 10 + 2*m_size;
					m_data = (int*)realloc(m_data,m_size * sizeof(int));
				}
				m_data[m_tail++] = a;
			}
			
			bool empty() {
				return (m_head == m_tail);
			}
};