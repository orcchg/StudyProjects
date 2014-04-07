#include <cstdlib>

class Deck {
			int* m_data;
			int m_size_t;
			int m_size_h;
			int m_tail;
			int m_head;
			
	public:
			Deck(int size) {
				m_size_t = size;
				m_size_h = size;
				m_data = (int*)malloc(m_size_t * sizeof(int));
				m_tail = 0;
				m_head = 0;
			}
			~Deck() {
				free(m_data);
			}
			
			int take_tail(void) {
				if(m_head != m_tail)
					return m_data[--m_tail];
				else
					return -999;
			}
			
			int take_head(void) {
				if(m_head != m_tail)
					return m_data[m_head++];
				else
					return -999;
			}
					
			void add_tail(int a) {
				if(m_tail >= m_size_t-1) {
					m_size_t = 10 + 2*m_size_t;
					m_data = (int*)realloc(m_data, m_size_t * sizeof(int));
				}
				m_data[m_tail++] = a;
			}
			
			void add_head(int a) {
				if(m_head == 0) {
					m_size_h = 10 + 2*m_size_h;
					m_data = (int*)realloc(m_data, m_size_h * sizeof(int));
				}
				m_data[--m_head] = a;
			}
			
			bool empty() {
				return (m_head == m_tail);
			}
};