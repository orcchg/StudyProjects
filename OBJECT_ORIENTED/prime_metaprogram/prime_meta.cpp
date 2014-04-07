template <int P, int I>
	struct IsPrime {
		enum { prime = (P == 2) || (P % I) &&
            IsPrime<(I > 2 ? P : 0), I Ц 1>::prime };
	};

	template <>
	struct IsPrime<0, 0> {
		enum { prime = 1};
	};

	template<>
	struct IsPrime<0, 1> {
		enum { prime = 1};
	};

	template <int I>
	struct F {
		F(void*);
	};

	template <int I>
	struct PrintPrime {
        PrintPrime<I Ц 1> a;
        enum { prime = IsPrime<I, I Ц 1>::prime };
		void f() {
			F<I> instance = prime ? 1 : 0;
			a.f();
		}
	};

	// —пециализаци€ шаблона дл€ окончани€ рекурсии
	template<>
	struct PrintPrime<1> {
		enum { prime = 0 };
		void f() {
			F<1> instance = prime ? 1 : 0;
		};
	};

	int main() {
		PrintPrime<20> a;
		a.f();
		return 0;
	}
