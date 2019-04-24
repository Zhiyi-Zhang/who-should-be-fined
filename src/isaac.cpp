#include "isaac.hpp"

template<>
void isaac64_engine::seed(std::seed_seq& s)
{
	std::uint32_t vals[randsiz() << 1];
	s.generate(vals, vals + (randsiz() << 1));
	for (std::size_t i=0, j=0; i<randsiz()<<1; i+=2, ++j) {
		this->m_randrsl[j] = (std::uint64_t(vals[i]) << 32) | vals[i+1];
	}
	this->init();
}