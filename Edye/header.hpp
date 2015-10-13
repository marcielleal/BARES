#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP
#include <iostream>

template<typename P>
class Pilha{
	protected:
		P *pt_Pilha;
		int tamanho;
		int capacidade;
		bool _duplica(void);
	public:
		Pilha(int _MaxSz=25);
		~Pilha(void);

		bool pop();
		bool push(P _data);
		P top();
		int size() const;
		bool full() const;
		bool empty() const;


		inline friend
		std::ostream &operator <<(std::ostream &_os,const Pilha &_obj){
			_os<<"[ ";
			for(int i=0;i<_obj.tamanho;i++)
				_os<<_obj.pt_Pilha[i]<< " ";
			_os<<" ]"<<std::endl;
			return _os;
		}
};
template<typename F>
class Fila{
	protected:
		F *pt_fila;
		int _MaxSz;
		int inicio;
		int fim;
		int tamanho;
	public:
		Fila(int _MaxSz=20);
		~Fila(void);

		F front() const;
		F back() const;
        bool pop();
		bool push(F _data);
		bool full() const;
		bool empty() const;
        int size() const;

        inline friend
		std::ostream &operator <<(std::ostream &_os,const Fila &_obj){
			_os<<"[";
			for(int i=0;i<_obj.tamanho;i++)
				_os<<_obj.pt_fila[(_obj.inicio+i)%_obj._MaxSz]<<" ";
			_os<<"]"<<std::endl;
			return _os;
		}
};


#endif
