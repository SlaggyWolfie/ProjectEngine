#ifndef SixthScene_HPP
#define SixthScene_HPP

#include "mge/core/AbstractGame.hpp"
class DebugHud;

namespace MyGame
{

	/**
	 * An example subclass of AbstractGame showing how we can setup a scene.
	 */
	class SixthScene : public AbstractGame
	{
		//PUBLIC FUNCTIONS

	public:
		SixthScene();
		virtual ~SixthScene();

		//override initialize so we can add a DebugHud
		virtual void initialize();

	protected:
		//override so we can construct the actual scene
		virtual void _initializeScene();

		//override render to render the hud as well.
		virtual void _render();

	private:
		DebugHud* _hud;                   //hud display

		void _updateHud();

		SixthScene(const SixthScene&);
		SixthScene& operator=(const SixthScene&);
	};
}
#endif // SixthScene_HPP