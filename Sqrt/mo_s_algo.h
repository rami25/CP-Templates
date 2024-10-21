namespace mo_s_algo { 
  using mo_info = int;
  using mo_answer = int;
  
  // TODO: re-implement this struct.
  template <class T, class U> struct mo_state {
      const vector<T> &info;

      mo_state(const vector<T> &_info) : info(_info) {
      }
  
      void add_left(int index) {
      }
  
      void add_right(int index) {
      }
  
      void remove_left(int index) {
      }
  
      void remove_right(int index) {
      }
  
      U get_answer() const {
		  return U();
      }
  };
  
  struct mo_query {
      int start, end, block, index;
  
      mo_query() : start(0), end(0) {}
  
      mo_query(int _start, int _end) : start(_start), end(_end) {}
  
      bool operator<(const mo_query &other) const {
          if (block != other.block)
              return block < other.block;
  
          return block % 2 == 0 ? end < other.end : end > other.end;
      }
  };
  
  template <class T = mo_info, class U = mo_answer> struct mo {
      int n;
      vector<T> info;
  
      mo(const vector<T> &_info = {}) : info(_info) {
          n = int(info.size());
      }
  
      void update_state(mo_state<T, U> &state, const mo_query &first, const mo_query &second) const {
          if (max(first.start, second.start) >= min(first.end, second.end)) {
              for (int i = first.start; i < first.end; i++)
                  state.remove_left(i);
  
              for (int i = second.start; i < second.end; i++)
                  state.add_right(i);
  
              return;
          }
  
          for (int i = first.start - 1; i >= second.start; i--)
              state.add_left(i);
  
          for (int i = first.end; i < second.end; i++)
              state.add_right(i);
  
          for (int i = first.start; i < second.start; i++)
              state.remove_left(i);
  
          for (int i = first.end - 1; i >= second.end; i--)
              state.remove_right(i);
      }
  
      vector<U> solve(vector<mo_query> &queries) const {
          int block_size = int(1.5 * n / sqrt(max(int(queries.size()), 1)) + 1);
  
          for (int i = 0; i < int(queries.size()); i++) {
              queries[i].index = i;
              queries[i].block = queries[i].start / block_size;
          }
  
          sort(queries.begin(), queries.end());
          mo_state<T, U> state(info);
          mo_query last_query;
          vector<U> answers(queries.size());
  
          for (mo_query &q : queries) {
              update_state(state, last_query, q);
              answers[q.index] = state.get_answer();
              last_query = q;
          }
  
          return answers;
      }
  };
}  // namespace mo_s_algo
using namespace mo_s_algo;