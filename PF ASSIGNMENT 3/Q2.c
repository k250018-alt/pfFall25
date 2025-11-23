#include <stdio.h>

typedef struct {
    int current_planet;
    int recharge_planet;
    int max_planet;
} Planet;

typedef struct {
    int fuel;
    int fuel_cost;
    int recharge;
    int solar_recharge;
} Ship;

typedef struct {
    Planet p;
    Ship sh;
} Space;

void calc_fuel(Space* s){
	if (s->sh.fuel <= 0){
		printf("You couldnt reach your destination");
		return;
	}
	else if( s->p.current_planet == s->p.max_planet){
		printf("You reached your destination ");
		return;
	}else{
		if(s->p.current_planet % s->p.recharge_planet == 0){
			s->sh.fuel = s->sh.fuel + s->sh.recharge;
		}
		if(s->p.current_planet % 4 == 0){
			s->sh.fuel = s->sh.fuel + s->sh.solar_recharge;
		}
		s->p.current_planet++;
		s->sh.fuel = s->sh.fuel - s->sh.fuel_cost;
		printf("You Have reached the %d planet and %d fuel is remaining in the ship \n",s->p.current_planet,s->sh.fuel);
		calc_fuel(s);
	}
	
}
int main() {
	
    Space s;
	s.p.current_planet = 0 ;
    printf("ENTER THE FUEL : ");
    scanf("%d", &s.sh.fuel);
    printf("ENTER THE FUEL COST TO TRAVEL: ");
    scanf("%d", &s.sh.fuel_cost);
    printf("ENTER THE MAX PLANET : ");
    scanf("%d", &s.p.max_planet);
    printf("ENTER THE FREQUENCY AFTER WHICH PLANETS RECHARGE THE SHIP : ");
    scanf("%d", &s.p.recharge_planet);
    printf("ENTER THE AMOUNT RECHARGED : ");
    scanf("%d", &s.sh.recharge);
    printf("ENTER THE SOLAR RECHARGE : ");
    scanf("%d", &s.sh.solar_recharge);

	calc_fuel(&s);
    return 0;
}
                   