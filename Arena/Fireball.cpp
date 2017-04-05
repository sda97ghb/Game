#include "Box2D/Common/b2Math.h"

#include "Arena/Fireball.h"
#include "Arena/Log.h"
#include "Arena/Player.h"
#include "Arena/World.h"

static int count = 0;

void Fireball::spawn(float x, float y)
{
    if (count > 10)
        return;
    ++ count;

    Fireball& fireball = World::instance().createFireball();
    fireball.setPosition(x, y);

    SpriteAnimator& animator = fireball.spriteAnimator();
    animator.setTexture("Textures/fireball.png");
    animator.setAnimationGroup("main", 0, 0, 4, 4, 1, false);
    animator.setAnimationGroup("dead", 0, 0, 4, 4, 1, false);
    animator.setCurrentGroup("main");
    animator.nextFrame();
}

Fireball::Fireball() :
    _state(State::going_to_player)
{
}

float Fireball::width() const
{
    return 0.01f;
}

float Fireball::height() const
{
    return 0.01f;
}

void Fireball::update()
{
    if (!isAlive())
    {
        body().SetTransform(b2Vec2(100.0f, 500.0f), 0.0f);
        body().SetAwake(false);
        return;
    }

    body().ApplyForce(b2Vec2(0.0f, body().GetMass() * 9.8), body().GetWorldCenter(), true);

    lookForPlayer();

    if (!canSeePlayer())
        return;

    b2Vec2 r = Player::instance().body().GetPosition() -
                     this->body().GetPosition();

    if (r.Length() < 1.5f)
    {
        strike();
        return;
    }

    r.Normalize();
    r *= body().GetMass() * 1.0f;
    body().ApplyLinearImpulse(r, body().GetWorldCenter(), true);

    _spriteAnimator.playGroup("main");
}

void Fireball::strike()
{
    kill();
    -- count;
    Log::instance().push("Boom!");
    Player::instance().makeDamage(3.0f);
}
