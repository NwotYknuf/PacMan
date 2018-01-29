#ifndef CHARACTER_H
#define CHARACTER_H

template<class I, class P>
class Character {

public:

	I info;
	P position;

	template< class WINDOW>
	bool Character<I>::drawCharacter(WINDOW & window) const;

};

template <class I>
template< class WINDOW>
bool Character<I>::drawCharacter(WINDOW & window) const{

	if(!window.draw(pA->value)
		return false;

	return true;

}

#endif // !CHARACTER_H
