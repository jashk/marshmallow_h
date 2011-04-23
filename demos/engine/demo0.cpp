/*
 * Copyright 2011 Marshmallow Engine. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice, this list of
 *      conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice, this list
 *      of conditions and the following disclaimer in the documentation and/or other materials
 *      provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY MARSHMALLOW ENGINE ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MARSHMALLOW ENGINE OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of Marshmallow Engine.
 */

#include "core/platform.h"
#include "math/vector2.h"
#include "event/debugeventlistener.h"
#include "event/eventbase.h"
#include "event/eventmanager.h"
#include "graphics/painter.h"
#include "graphics/quadgraphic.h"
#include "graphics/textureasset.h"
#include "graphics/viewport.h"
#include "game/engine.h"
#include "game/entity.h"
#include "game/icomponent.h"
#include "game/movementcomponent.h"
#include "game/positioncomponent.h"
#include "game/rendercomponent.h"
#include "game/scenebase.h"
#include "game/scenemanager.h"

MARSHMALLOW_NAMESPACE_USE;
using namespace Core;

class DemoBounceComponent : public Game::ComponentBase
{

	Game::WeakPositionComponent m_position;
	Game::WeakMovementComponent m_movement;

public:
	DemoBounceComponent(Game::WeakEntity e)
	: Game::ComponentBase("bouncer", e)
	{
	}

	VIRTUAL void update(TIME d)
	{
		if (!entity()) return;
		UNUSED(d);

		if (!m_position)
			m_position = entity()->componentType("Game::PositionComponent").
			    cast<Game::PositionComponent>();

		if (!m_movement)
			m_movement = entity()->componentType("Game::MovementComponent").
			    cast<Game::MovementComponent>();

		if (m_position && m_movement) {
			INFO("DELTA: %f", d);
			INFO("Current position %f, %f",
			    m_position->position().rx(), m_position->position().ry());

			Math::Size2 l_vpsize = Graphics::Viewport::Size();

			Math::Point2  &pos = m_position->position();
			Math::Vector2 &dir = m_movement->direction();

			if ((pos.rx() <= -l_vpsize.width() / 2 && dir.rx() < 0)
			 || (pos.rx() >=  l_vpsize.width() / 2 && dir.rx() > 0))
				dir.rx() *= -0.95f;
			if ((pos.ry() <= -l_vpsize.height() / 2 && dir.ry() < 0)
			 || (pos.ry() >=  l_vpsize.height() / 2 && dir.ry() > 0))
				dir.ry() *= -0.95f;
		}
	}

	VIRTUAL const Core::Type & type(void) const
	{
		static const Core::Type s_type("DemoBounceComponent");
		return(s_type);
	}
};

class DemoScene : public Game::SceneBase
{
	bool m_init;
	Graphics::SharedTextureAsset m_asset; // move to scene asset manager

public:

	DemoScene(void)
	: SceneBase("DemoScene"),
	  m_init(false),
	  m_asset(new Graphics::TextureAsset)
	  {}

	VIRTUAL void activate(void)
	{
		SceneBase::activate();

		if (!m_init) {
			m_init = true;
			Game::SharedEntity l_entity(new Game::Entity("player"));

			Game::PositionComponent *l_pcomponent =
			    new Game::PositionComponent("position", l_entity);
			l_entity->addComponent(l_pcomponent);

			Game::MovementComponent *l_mcomponent =
			    new Game::MovementComponent("movement", l_entity);
			l_mcomponent->direction() = Math::Vector2(150, 150);
			if (rand() % 2)
			    l_mcomponent->direction().rx() *= -1;
			if (rand() % 2)
			    l_mcomponent->direction().ry() *= -1;
			l_entity->addComponent(l_mcomponent);

			DemoBounceComponent *l_bcomponent = new DemoBounceComponent(l_entity);
			l_entity->addComponent(l_bcomponent);

			m_asset->load("demos/engine/assets/mallow.png");
			Math::Rect2 l_rect(Math::Point2::Null, m_asset->size());
			Game::RenderComponent *l_rcomponent =
			    new Game::RenderComponent("render", l_entity);
			l_rcomponent->graphic() = new Graphics::QuadGraphic(l_rect);
			l_rcomponent->graphic()->setTexture(m_asset);
			l_entity->addComponent(l_rcomponent);

			addEntity(l_entity);
		}
	}

	VIRTUAL const Core::Type & type(void) const
	{
		static const Core::Type s_type("DemoScene");
		return(s_type);
	}
};

class Demo : public Game::Engine
{
	int m_stop_timer;
	Event::SharedEventListener m_debugListener;

public:

	Demo(void)
	: Engine(),
	  m_stop_timer(0),
	  m_debugListener(new Event::DebugEventListener("log.txt"))
	{
	}

	VIRTUAL void initialize(void)
	{
		Engine::initialize();

#if 0
		Graphics::Viewport::Redisplay(640, 480);
		eventManager()->connect(m_debugListener, "Event::RenderEvent");
		eventManager()->connect(m_debugListener, "Event::UpdateEvent");
#endif
		eventManager()->connect(m_debugListener, "Event::KeyboardEvent");

		Game::SharedScene l_scene(new DemoScene);
		sceneManager()->push(l_scene);
	}

	VIRTUAL void finalize(void)
	{
		Engine::finalize();
	}

	VIRTUAL void second(void)
	{
		Engine::second();

		if (++m_stop_timer == 30)
			stop();
	}
};

int
main(void)
{
	return(Demo().run());
}

