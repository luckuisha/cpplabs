#include <galaxy-explorer/GameAI.hpp>
#include <galaxy-explorer/MyAIData.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>


GameAI::GameAI(const GameInfo& game_info, sf::RenderTarget* debug_rt)
{
	this->debug_rt = debug_rt;
	this->game_info = game_info;
	this->asteroid_observer = AsteroidsObserver(this);
	this->my_game_ai = new MyAIData();

	// customState().debug_on = false;
}

GameAI::~GameAI() {
	delete my_game_ai;
}

SuggestedAction GameAI::suggestAction(const ShipState& ship_state) {
      
	debug_rt->clear(sf::Color::Transparent);
     	if (customState().debug_on) {
		if (not asteroidsObserver().asteroids().isEmpty()) {
			const sf::IntRect first_ast_hb = asteroidsObserver().asteroids().front().getCurrentHitbox();
			sf::RectangleShape ast_rect(sf::Vector2f(first_ast_hb.width, first_ast_hb.height));
			ast_rect.setPosition(first_ast_hb.left, first_ast_hb.top);
			ast_rect.setOutlineThickness(33.0f); // if lines are too thin, they won't show up sometimes
			ast_rect.setOutlineColor(sf::Color::Yellow);
			ast_rect.setFillColor(sf::Color::Transparent);
			debug_rt->draw(ast_rect);
		} 
	}
        
        
//     printf("board x: %d \n" , game_info.field_shape.top);
//     printf("board y: %d \n" , game_info.field_shape.left);
//     printf("board width: %d \n" , game_info.field_shape.width);
//     printf("board height: %d \n" , game_info.field_shape.height);
//     printf("ship y: %d \n" , ship_state.hitbox.top);
//     printf ("%d\n ", ship_state.millidegree_rotation);
        
        //double angle = atan2( asteroidsObserver().asteroids().front().getVelocity().y, asteroidsObserver().asteroids().front().getVelocity().x)*180/M_PI-90;
//        double max = sqrt(pow(game_info.field_shape.height,2) + pow(ship_state.hitbox.left+ship_state.hitbox.width,2));
//        AsteroidListItem * ptr = asteroidsObserver().asteroids().begin();
//        Asteroid As = asteroidsObserver().asteroids().front();
        sf::Vector2i line;
        //sf::Vector2i ship (ship_state.hitbox.left, ship_state.hitbox.top);      
        
//        while (ptr != NULL)
//        {
//            sf::Vector2i direction ((As.getVelocity().x),(As.getVelocity().y));
//            sf::Vector2i initial (As.getCurrentHitbox().left, 0);
//           // printf(" %d, %d\n", 20000- ship_state.hitbox.top, ship_state.hitbox.height);
//            
//            for (int cnt = 1; cnt < max; cnt++)
//            {
//                line = initial+cnt*direction;
//                if (line.x < 0 || line.x > game_info.field_shape.width || line.y > game_info.field_shape.height + 90)
//                    break;
//               // printf("line x, y = %d, %d\n", line.x, line.y);
//               // printf("left, right, top, bottom %d, %d, %d, %d\n", ship_state.hitbox.left, ship_state.hitbox.left + ship_state.hitbox.width, ship_state.hitbox.top, ship_state.hitbox.top +ship_state.hitbox.height);
//                if (line.x + As.getCurrentHitbox().width <= ship_state.hitbox.left + ship_state.hitbox.width //plus dx???
//                        && line.x >= ship_state.hitbox.left
//                        && line.y >= ship_state.hitbox.top
//                        && line.y <=ship_state.hitbox.top +ship_state.hitbox.height)
//                {//take width of asteroid
//                    this->my_game_ai->id = ptr->getData().getID();
//                    printf("%d\n", this->my_game_ai->id);
//                }
//            }
//            ptr = ptr->getNext();
//        }
//        
        
        
        
        if (this->my_game_ai->state == 0)
        {
            if (ship_state.millidegree_rotation >= 34*1000)
                {
                    this->my_game_ai->state = 1;
                }
            return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
           
        }
        else if (this->my_game_ai->state == 1)
        {
             if (ship_state.millidegree_rotation <= -34*1000)
            {
                this->my_game_ai->state = 2;
            }
            return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
        }
        else if (this->my_game_ai->state == 2)
        {
             if (ship_state.millidegree_rotation >= 32*1000)
            {
                this->my_game_ai->state = 3;
            }
            return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
        }
        else if (this->my_game_ai->state == 3)
        {
             if (ship_state.millidegree_rotation <= -32*1000)
            {
                this->my_game_ai->state = 0;
            }
            return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
        }
//        else if (this->my_game_ai->state == 4)
//        {
//             if (ship_state.millidegree_rotation >= rand()%105*1000)
//            {
//                this->my_game_ai->state = 5;
//            }
//            return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
//        }
//        else if (this->my_game_ai->state == 5)
//        {
//             if (ship_state.millidegree_rotation <= -rand()%105*1000)
//            {
//                this->my_game_ai->state = 0;
//            }
//            return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
//        }
        return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
//	return SimpleActions::START_YAWING_CW;
	//return SimpleActions::START_YAWING_ACW;
	//return SimpleActions::STOP_YAWING_AND_FIRE;
	//return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
}
