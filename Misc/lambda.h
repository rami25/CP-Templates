// lambda recursive call
template <class F> struct Function { 
  F f;
  Function(const F &f) : f(f) {} // NOLINT(*-explicit-constructor)

  template <class... Args>
  constexpr decltype(auto) operator()(Args &&... args) const {
	  return f(*this, std::forward<Args>(args)...); 
  }
};

template <class F> Function(const F &) -> Function<F>;