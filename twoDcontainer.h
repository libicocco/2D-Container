#include <boost/iterator/iterator_facade.hpp>
#include <vector>
#include <list>

template <typename T, 
          template<class,class> class InnerCont = std::vector,
          template<class,class> class OuterCont = std::vector>
class Container2D : public OuterCont<InnerCont<T, std::allocator<T> >, std::allocator<T> >{

    public:

        typedef InnerCont<T, std::allocator<T> > InnerContT;
        typedef typename InnerContT::iterator InnerContT_it;
        typedef OuterCont<InnerContT, std::allocator<T> > OuterContT;
        typedef typename OuterContT::iterator OuterContT_it;
        typedef std::list<InnerContT_it> LimitsContT;


    class twoD_iterator :
        public boost::iterator_facade< twoD_iterator, int, boost::forward_traversal_tag>{
            typedef InnerCont<T, std::allocator<T> > InnerContT;
            typedef typename InnerContT::iterator InnerContT_it;
            typedef OuterCont<InnerContT, std::allocator<T> > OuterContT;
            typedef std::list<InnerContT_it> LimitsContT;
    
            public:
                explicit twoD_iterator(const InnerContT_it it, const LimitsContT& begins, const LimitsContT& ends):
                    m_it(it), m_begins(begins), m_ends(ends){}
            private:
                friend class boost::iterator_core_access;
                void increment() {
                    m_it++;
                    if(m_it == m_ends.front() && !m_begins.empty()){
                        m_it = m_begins.front();
                        m_begins.pop_front();
                        m_ends.pop_front();
                    }
                }
                bool equal(twoD_iterator const& other) const
                {
                    return m_it == other.m_it;
                }
                T& dereference() const { return *m_it; }
    
                InnerContT_it m_it;
                LimitsContT m_begins;
                LimitsContT m_ends;
        };
    
        Container2D():OuterContT(),computed_begins_ends(false){}

        void compute_begins_ends(){
            for(OuterContT_it it = this->begin(); it != this->end(); ++it){
                if(it != this->begin())
                    begins.push_back(it->begin());
                ends.push_back(it->end());
            }
            computed_begins_ends = true;
        }

        twoD_iterator global_begin(){
            if (!computed_begins_ends)
                compute_begins_ends();
            return twoD_iterator(this->front().begin(), begins, ends);
        }
        twoD_iterator global_end(){
            return twoD_iterator(this->back().end(), LimitsContT(), LimitsContT());
        }

    private:
        bool computed_begins_ends;
        LimitsContT begins, ends;
};


