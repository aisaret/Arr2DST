#include <stdint.h>
#include <stdlib.h>

/*
for educational purposes only by Aisaret
*/

namespace alg {
	template <typename T=char>
		class Array2D_ST {
			private:
				uint32_t NR;		// num of rows
				uint32_t NC;		// num of columns
				T * m_data;			// the place where the array resides.
				uint32_t m_size;		// the size of the array
				T * m_data_ptr;		// the pointer to the data
				uint32_t m_data_size;	// the size of the data
				uint32_t m_data_capacity;	// the capacity of the data
				uint32_t m_encode_size;	// the size of the encode

			public:
				Array2D_ST(uint32_t nrow, uint32_t ncol, T val) {
					NR = nrow;
					NC = ncol;	
					m_data = new T[nrow*ncol];
					for (uint32_t i=0; i<nrow*ncol; i++) {
						m_data[i] = val;
					}
				}
				~Array2D_ST() {
					delete [] m_data;
				}

				void encode_size() {
					m_encode_size = 0;
					for (uint32_t i=0; i<m_data_size; i++) {
						m_encode_size += sizeof(T);
					}
				}

				uint32_t encode_capacity(T * & data) {
					encode();
					data = new T[m_encode_size];
					uint32_t i;
					for (i=0; i<m_data_size; i++) {
						data[i] = m_data[i];
					}
					return m_encode_size;
				}

				void encode_un() {
					m_data_ptr = (T *)m_data;
					m_data_size = NR*NC;
					m_data_capacity = m_data_size;
					encode_size();
				}

			private:
				Array2D_ST(const Array2D_ST&);	
				Array2D_ST& operator=(const Array2D_ST&);	

			public:
				inline const uint32_t row() const { return NR; }
				inline const uint32_t col() const { return NC; }
				inline const uint32_t size() const { return NR*NC; }

				inline T* operator[](uint32_t i) {
					return m_data + i*NC;
				}

				inline T& operator() (int row, int col) { return this->m_data[row*NC + col]; }
				const inline T& operator() (int row, int col) const { return this->m_data[row*NC + col]; }

				inline T* operator[] (int row) { return &(m_data[row * NC]); }
				inline const T* operator[] (int row) const { return &(m_data[row * NC]); }

				inline T& operator() (const alg::Double& d) { return this->m_data[d.row*NC + d.col]; }

				inline void encode() { encode_un(); }

				void clear(const T & value, uint32_t row, uint32_t col) {
					for(uint32_t i=0; i<NR;i++){
						for(uint32_t j=0; j<NC;j++){
							if(i==row && j==col){
								m_data[i*NC + j] = value;
							}
						}
					}
				}

				void clear_un(const T & value, uint32_t row, uint32_t col) {
					encode_un();
					for(uint32_t i=0; i<NR;i++){
						for(uint32_t j=0; j<NC;j++){
							if(i==row && j==col){
								m_data[i*NC + j] = value;
							}
						}
					}
				}
	

		};
}

