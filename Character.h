#ifndef CHARACTER_H
#define CHARACTER_H

template<class I, class P>
class Character {

public:

	I info;
	P position;

	Character(I _info, P _pos) {
		info = _info;
		position = _pos;
	}

	template< class WINDOW>
	bool drawCharacter(WINDOW & window) const;

};

template <class I, class P>
template< class WINDOW>
bool Character<I,P>::drawCharacter(WINDOW & window) const{

	if(!window.draw(this))
		return false;

	return true;

}

#endif // !CHARACTER_H
