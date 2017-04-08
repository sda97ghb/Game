#include "Box2D/Common/b2Math.h"

#include "Arena/Log.h"
#include "Arena/World.h"

#include "Arena/Entity/Fireball.h"
#include "Arena/Entity/Player.h"

static int count = 0;

void Fireball::spawn(float x, float y)
{
    if (count > 10)
        return;
    ++ count;

    Fireball& fireball = World::instance().createFireball();
    fireball.setPosition(x, y);

    fireball.body().SetGravityScale(0.0f);

    SpriteAnimator& animator = fireball.spriteAnimator();
    animator.setTexture("Textures/fireball.png");
    animator.setAnimationGroup("main", 0, 0, 4, 4);
    animator.setAnimationGroup("dead", 0, 0, 4, 4);
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

    lookForPlayer();

    if (!canSeePlayer())
        return;

    b2Vec2 r = Player::instance().body().GetPosition() -
                     this->body().GetPosition();

    if (r.Length() < 1.5f)
    {
        boom();
        return;
    }

    r.Normalize();
    r *= body().GetMass() * 1.0f;
    body().ApplyLinearImpulse(r, body().GetWorldCenter(), true);

    _spriteAnimator.playGroup("main");
}

void Fireball::boom()
{
    kill();
    -- count;
    Log::instance().push("Boom!");
    Player::instance().makeDamage(3.0f);
}
