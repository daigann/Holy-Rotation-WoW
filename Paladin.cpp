#include "Paladin.h"
#include <iostream>


Paladin::Paladin(TargetDummy *dumbdumb) 
{
	critChance = 15; damageMultiplier = 1.0; meleeTimeTillNextSwing = 2.3; gcdTimeLeft = 0; holyPower = 0; consecrationActive = false; consecrationActiveTimeLeft = 0;
	consecrationTimeTillNextDamage = 0; glimmerOfLightActive = false; shieldOfRighteousCdLeft = 0;
	consecrationCdLeft = 0; judgmentBuffActive = false; judgmentCdLeft = 0; avengingWrathActive = false; avengingWrathCdLeft = 0; avengingWrathTimeLeftOnBuff = 0;
	holyShockCdLeft = 0; crusaderStrikeCdLeftOne = 0; crusaderStrikeCdLeftTwo = 0; crusaderStrikeCharges = 2; holyPrismCdLeft = 0; holyAvengerActive = 0; holyAvengerCdLeft = 0;
	holyAvengerActiveTimeLeft = 0; hammerOfWrathCdLeft = 0; 
	dreadFireAvailable = true; glyphAvailable = true; glyphTimeOnTargetLeft = 0; glyphTimeTillNextAttack = 0; glyphActiveOnTarget = false;

	blessingOfSummerActive = true; blessingOfFallActive = false; blessingOfSpringActive = false; blessingOfWinterActive = false;
	target = dumbdumb;
	srand((unsigned)time(0));
}

void Paladin::castConsecration()
{
	if (gcdTimeLeft == 0)
	{
		if (consecrationCdLeft == 0)
		{
			// this is an aoe so just set the appropriate variables then upon cycle it'll do its thing
			consecrationActive = true;
			consecrationActiveTimeLeft = 12;
			consecrationCdLeft = 8.6;
			consecrationTimeTillNextDamage = .8;
			gcdTimeLeft = 1.2;

			// consecration does an initial hit can crit
			// if the random number is equal to or below or crit % then we crit strike
			if ((rand() % 100) <= critChance)
			{
				target->totalDamageDone += ((310 * damageMultiplier) * 2);
			}

			else
			{
				target->totalDamageDone += (310 * damageMultiplier);
			}
		}
	}
}

void Paladin::consecration()
{
	if (consecrationActiveTimeLeft > 0)
	{
		consecrationActiveTimeLeft -= .1;

		if (consecrationActiveTimeLeft <= 0)
		{
			consecrationActive = false;
			consecrationActiveTimeLeft = 0;
			consecrationTimeTillNextDamage = 0;
		}
	}

	if (consecrationCdLeft > 0)
	{
		consecrationCdLeft -= .1;

		if (consecrationCdLeft <= 0)
		{
			consecrationCdLeft = 0;
		}
	}

	if (consecrationTimeTillNextDamage > 0)
	{
		consecrationTimeTillNextDamage -= .1;

		if (consecrationTimeTillNextDamage <= 0)
		{
			if ((rand() % 100) <= critChance)
			{
				target->totalDamageDone += ((310 * damageMultiplier) * 2);
			}

			else
			{
				target->totalDamageDone += (310 * damageMultiplier);
			}
			
			consecrationTimeTillNextDamage = .8;
		}
	}
}

void Paladin::castCrusaderStrike()
{
	if (gcdTimeLeft == 0 && crusaderStrikeCharges > 0)
	{
		// take a charge of crusader strike away, refils at crusaderSTrike() function
		crusaderStrikeCharges--;
		
		gcdTimeLeft = 1.2;

		// generates 1 holy power unless buff is active then generates 3
		if (holyAvengerActive)
		{
			holyPower += 3;

			if (holyPower > maxHolyPower)
			{
				holyPower = maxHolyPower;
			}
		}

		else
		{
			holyPower++;

			if (holyPower > maxHolyPower)
			{
				holyPower = maxHolyPower;
			}
		}

		if ((rand() % 100) <= critChance)
		{
			int tempDamage = (((1600 * damageMultiplier) * 2) * .7);

			if (judgmentBuffActive)
			{
				tempDamage *= 1.3;

				judgmentBuffActive = false;
			}

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}

		else
		{
			int tempDamage = ((1600 * damageMultiplier) * .7);

			if (judgmentBuffActive)
			{
				tempDamage *= 1.3;

				judgmentBuffActive = false;
			}

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}

		// put one of the charges on cooldown
		if (crusaderStrikeCdLeftOne == 0)
		{
			crusaderStrikeCdLeftOne = 4.5;
		}

		else if (crusaderStrikeCdLeftOne > 0 && crusaderStrikeCdLeftTwo == 0)
		{
			crusaderStrikeCdLeftTwo = 4.5;
		}
	}
}

void Paladin::crusaderStrike()
{
	if (crusaderStrikeCdLeftOne > 0)
	{
		crusaderStrikeCdLeftOne -= .1;

		if (crusaderStrikeCdLeftOne <= 0)
		{
			crusaderStrikeCdLeftOne = 0;
			crusaderStrikeCharges++;
		}
	}

	if (crusaderStrikeCdLeftTwo > 0)
	{
		crusaderStrikeCdLeftTwo -= .1;

		if (crusaderStrikeCdLeftTwo <= 0)
		{
			crusaderStrikeCdLeftTwo = 0;
			crusaderStrikeCharges++;
		}
	}
}

void Paladin::castJudgment()
{
	if (gcdTimeLeft == 0 && judgmentCdLeft == 0)
	{
		judgmentCdLeft = 10;
		gcdTimeLeft = 1.2;

		judgmentBuffActive = true;

		// generates 1 holy power unless buff is active then generates 3
		if (holyAvengerActive)
		{
			holyPower += 3;

			if (holyPower > maxHolyPower)
			{
				holyPower = maxHolyPower;
			}
		}

		else
		{
			holyPower++;

			if (holyPower > maxHolyPower)
			{
				holyPower = maxHolyPower;
			}
		}

		if ((rand() % 100) <= critChance)
		{
			int tempDamage = ((4600 * damageMultiplier) * 2);

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}

		else
		{
			int tempDamage = (4600 * damageMultiplier);

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}
	}
}

void Paladin::judgment()
{
	if (judgmentCdLeft > 0)
	{
		judgmentCdLeft -= .1;

		if (judgmentCdLeft <= 0)
		{
			judgmentCdLeft = 0;
		}
	}
}

void Paladin::castShieldOfRighteous()
{
	if (holyPower >= 3 && shieldOfRighteousCdLeft == 0)
	{
		holyPower -= 3;

		shieldOfRighteousCdLeft = .8;

		if ((rand() % 100) <= critChance)
		{
			int tempDamage = ((1300 * damageMultiplier) * 2);

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}

		else
		{
			int tempDamage = (1300 * damageMultiplier);

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}
	}
}

void Paladin::shieldOfRighteous()
{
	if (shieldOfRighteousCdLeft > 0)
	{
		shieldOfRighteousCdLeft -= .1;

		if (shieldOfRighteousCdLeft <= 0)
		{
			shieldOfRighteousCdLeft = 0;
		}
	}
}

void Paladin::castAvengingWrath()
{
	if (gcdTimeLeft == 0 && avengingWrathCdLeft == 0)
	{
		avengingWrathCdLeft = 120;

		avengingWrathActive = true;

		damageMultiplier += .2; critChance += 20;

		avengingWrathTimeLeftOnBuff = 25;

		gcdTimeLeft = 1.2;
	}
}

void Paladin::avengingWrath()
{
	if (avengingWrathCdLeft > 0)
	{
		avengingWrathCdLeft -= .1;

		if (avengingWrathCdLeft <= 0)
		{
			avengingWrathCdLeft = 0;
		}
	}

	if (avengingWrathTimeLeftOnBuff > 0)
	{
		avengingWrathTimeLeftOnBuff -= .1;

		if (avengingWrathTimeLeftOnBuff <= 0)
		{
			avengingWrathActive = false;

			damageMultiplier -= .2; critChance -= 20;

			avengingWrathTimeLeftOnBuff = 0;
		}
	}
}

void Paladin::castHolyShock()
{
	if (gcdTimeLeft == 0 && holyShockCdLeft == 0)
	{
		// generates 1 holy power unless buff is active then generates 3
		if (holyAvengerActive)
		{
			holyPower += 3;

			if (holyPower > maxHolyPower)
			{
				holyPower = maxHolyPower;
			}
		}

		else
		{
			holyPower++;

			if (holyPower > maxHolyPower)
			{
				holyPower = maxHolyPower;
			}
		}

		gcdTimeLeft = 1.2;

		if (avengingWrathActive)
		{
			holyShockCdLeft = 4;
		}
		
		else
		{
			holyShockCdLeft = 6.5;
		}
		
		if (glimmerOfLightActive)
		{
			if ((rand() % 100) <= critChance)
			{
				int tempDamage = ((450 * damageMultiplier) * 2);

				target->totalDamageDone += tempDamage;

				// calculate for blessing of summer and blessing of winter
				if (blessingOfSummerActive)
				{
					if ((rand() % 100) <= 40)
					{
						target->totalDamageDone += (tempDamage * .3);
					}
				}

				else if (blessingOfWinterActive)
				{
					target->totalDamageDone += (105 * damageMultiplier);
				}
			}

			else
			{
				int tempDamage = (450 * damageMultiplier);

				target->totalDamageDone += tempDamage;

				// calculate for blessing of summer and blessing of winter
				if (blessingOfSummerActive)
				{
					if ((rand() % 100) <= 40)
					{
						target->totalDamageDone += (tempDamage * .3);
					}
				}

				else if (blessingOfWinterActive)
				{
					target->totalDamageDone += (105 * damageMultiplier);
				}
			}
		}

		if ((rand() % 100) <= (critChance + 30))
		{
			int tempDamage = ((2300 * damageMultiplier) * 2);

			if (judgmentBuffActive)
			{
				tempDamage *= 1.3;

				judgmentBuffActive = false;
			}

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}

		else
		{
			int tempDamage = (2300 * damageMultiplier);

			if (judgmentBuffActive)
			{
				tempDamage *= 1.3;

				judgmentBuffActive = false;
			}

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}

		glimmerOfLightActive = true;
	}
}

void Paladin::holyShock()
{
	if (holyShockCdLeft > 0)
	{
		holyShockCdLeft -= .1;

		if (holyShockCdLeft <= 0)
		{
			holyShockCdLeft = 0;
		}
	}
}

void Paladin::castHolyAvenger()
{
	if (gcdTimeLeft == 0 && holyAvengerCdLeft == 0)
	{
		gcdTimeLeft = 1.25;

		holyAvengerActive = true;

		holyAvengerActiveTimeLeft = 20;

		holyAvengerCdLeft = 180;
	}
}

void Paladin::holyAvenger()
{
	if (holyAvengerActiveTimeLeft > 0)
	{
		holyAvengerActiveTimeLeft -= .1;

		if (holyAvengerActiveTimeLeft <= 0)
		{
			holyAvengerActive = false;

			holyAvengerActiveTimeLeft = 0;
		}
	}

	if (holyAvengerCdLeft > 0)
	{
		holyAvengerCdLeft -= .1;

		if (holyAvengerCdLeft <= 0)
		{
			holyAvengerCdLeft = 0;
		}
	}
}

void Paladin::castHolyPrism()
{
	if (gcdTimeLeft == 0 && holyPrismCdLeft == 0)
	{
		gcdTimeLeft = 1.2;

		holyPrismCdLeft = 20;

		if ((rand() % 100) <= critChance)
		{
			int tempDamage = ((1700 * damageMultiplier) * 2);

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}

		else
		{
			int tempDamage = (1700 * damageMultiplier);

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}
	}
}

void Paladin::holyPrism()
{
	if (holyPrismCdLeft > 0)
	{
		holyPrismCdLeft -= .1;

		if (holyPrismCdLeft <= 0)
		{
			holyPrismCdLeft = 0;
		}
	}
}

void Paladin::castHammerOfWrath()
{
	if (gcdTimeLeft == 0 && hammerOfWrathCdLeft == 0 && avengingWrathActive)
	{
		// generates 1 holy power unless buff is active then generates 3
		if (holyAvengerActive)
		{
			holyPower += 3;

			if (holyPower > maxHolyPower)
			{
				holyPower = maxHolyPower;
			}
		}

		else
		{
			holyPower++;

			if (holyPower > maxHolyPower)
			{
				holyPower = maxHolyPower;
			}
		}

		gcdTimeLeft = 1.2;

		hammerOfWrathCdLeft = 6.5;

		if ((rand() % 100) <= critChance)
		{
			int tempDamage = ((4200 * damageMultiplier) * 2);

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}

		else
		{
			int tempDamage = (4200 * damageMultiplier);

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}
	}
}

void Paladin::hammerOfWrath()
{
	if (hammerOfWrathCdLeft > 0)
	{
		hammerOfWrathCdLeft -= .1;

		if (hammerOfWrathCdLeft <= 0)
		{
			hammerOfWrathCdLeft = 0;
		}
	}
}

void Paladin::castDreadFireVessel()
{
	if (dreadFireAvailable)
	{
		dreadFireAvailable = false;
		
		if ((rand() % 100) <= critChance)
		{
			int tempDamage = ((10500 * damageMultiplier) * 2);

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}

		else
		{
			int tempDamage = (10500 * damageMultiplier);

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}
	}
}

void Paladin::castGlyphOfAssimilation()
{
	if (glyphAvailable)
	{
		glyphAvailable = false;
		
		glyphActiveOnTarget = true;

		glyphTimeOnTargetLeft = 9;

		glyphTimeTillNextAttack = .8;

		if ((rand() % 100) <= critChance)
		{
			int tempDamage = ((651 * damageMultiplier) * 2);

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}

		else
		{
			int tempDamage = (651 * damageMultiplier);

			target->totalDamageDone += tempDamage;

			// calculate for blessing of summer and blessing of winter
			if (blessingOfSummerActive)
			{
				if ((rand() % 100) <= 40)
				{
					target->totalDamageDone += (tempDamage * .3);
				}
			}

			else if (blessingOfWinterActive)
			{
				target->totalDamageDone += (105 * damageMultiplier);
			}
		}
	}
}

void Paladin::glyphOfAssimilation()
{
	if (glyphTimeOnTargetLeft > 0)
	{
		glyphTimeOnTargetLeft -= .1;
		
		if (glyphTimeOnTargetLeft <= 0)
		{
			glyphTimeOnTargetLeft = 0;
			
			glyphActiveOnTarget = false;
		}
	}
	
	if (glyphActiveOnTarget)
	{
		
		glyphTimeTillNextAttack -= .1;

		if (glyphTimeTillNextAttack <= 0)
		{
			glyphTimeTillNextAttack = .8;
			

			if ((rand() % 100) <= critChance)
			{
				int tempDamage = ((651 * damageMultiplier) * 2);

				target->totalDamageDone += tempDamage;

				// calculate for blessing of summer and blessing of winter
				if (blessingOfSummerActive)
				{
					if ((rand() % 100) <= 40)
					{
						target->totalDamageDone += (tempDamage * .3);
					}
				}

				else if (blessingOfWinterActive)
				{
					target->totalDamageDone += (105 * damageMultiplier);
				}
			}

			else
			{
				int tempDamage = (651 * damageMultiplier);

				target->totalDamageDone += tempDamage;

				// calculate for blessing of summer and blessing of winter
				if (blessingOfSummerActive)
				{
					if ((rand() % 100) <= 40)
					{
						target->totalDamageDone += (tempDamage * .3);
					}
				}

				else if (blessingOfWinterActive)
				{
					target->totalDamageDone += (105 * damageMultiplier);
				}
			}
		}
	}
}

void Paladin::melee()
{
	if (meleeTimeTillNextSwing > 0)
	{
		meleeTimeTillNextSwing -= .1;

		if (meleeTimeTillNextSwing <= 0)
		{
			meleeTimeTillNextSwing = 2.3;

			if ((rand() % 100) <= critChance)
			{
				int tempDamage = ((900 * damageMultiplier) * 2);

				target->totalDamageDone += tempDamage;

				// calculate for blessing of summer and blessing of winter
				if (blessingOfSummerActive)
				{
					if ((rand() % 100) <= 40)
					{
						target->totalDamageDone += (tempDamage * .3);
					}
				}

				else if (blessingOfWinterActive)
				{
					target->totalDamageDone += (105 * damageMultiplier);
				}
			}

			else
			{
				int tempDamage = (900 * damageMultiplier);

				target->totalDamageDone += tempDamage;

				// calculate for blessing of summer and blessing of winter
				if (blessingOfSummerActive)
				{
					if ((rand() % 100) <= 40)
					{
						target->totalDamageDone += (tempDamage * .3);
					}
				}

				else if (blessingOfWinterActive)
				{
					target->totalDamageDone += (105 * damageMultiplier);
				}
			}
		}
	}
}

void Paladin::reset()
{
	critChance = 15; damageMultiplier = 1.0; meleeTimeTillNextSwing = 2.3; gcdTimeLeft = 0; holyPower = 0; consecrationActive = false; consecrationActiveTimeLeft = 0;
	consecrationTimeTillNextDamage = 0; glimmerOfLightActive = false; shieldOfRighteousCdLeft = 0;
	consecrationCdLeft = 0; judgmentBuffActive = false; judgmentCdLeft = 0; avengingWrathActive = false; avengingWrathCdLeft = 0; avengingWrathTimeLeftOnBuff = 0;
	holyShockCdLeft = 0; crusaderStrikeCdLeftOne = 0; crusaderStrikeCdLeftTwo = 0; crusaderStrikeCharges = 2; holyPrismCdLeft = 0; holyAvengerActive = 0; holyAvengerCdLeft = 0;
	holyAvengerActiveTimeLeft = 0; hammerOfWrathCdLeft = 0;
	dreadFireAvailable = true; glyphAvailable = true; glyphTimeOnTargetLeft = 0; glyphTimeTillNextAttack = 0; glyphActiveOnTarget = false;

	blessingOfSummerActive = true; blessingOfFallActive = false; blessingOfSpringActive = false; blessingOfWinterActive = false;

	inputs.clear(); outputs.clear();
}

vector<double>& Paladin::getInputs()
{
	inputs.push_back(holyPower); inputs.push_back(consecrationActive); inputs.push_back(consecrationActiveTimeLeft); inputs.push_back(consecrationCdLeft); 
	inputs.push_back(judgmentBuffActive); inputs.push_back(judgmentCdLeft); inputs.push_back(avengingWrathActive); inputs.push_back(avengingWrathTimeLeftOnBuff);
	inputs.push_back(holyShockCdLeft); inputs.push_back(crusaderStrikeCdLeftOne); inputs.push_back(crusaderStrikeCdLeftTwo); inputs.push_back(holyPrismCdLeft);
	inputs.push_back(holyAvengerActive); inputs.push_back(holyAvengerActiveTimeLeft); inputs.push_back(hammerOfWrathCdLeft); inputs.push_back(dreadFireAvailable);
	inputs.push_back(glyphAvailable); inputs.push_back(glyphActiveOnTarget); inputs.push_back(glyphTimeOnTargetLeft); inputs.push_back(shieldOfRighteousCdLeft);
	inputs.push_back(glimmerOfLightActive);

	return inputs;
}

void Paladin::handleOutputs()
{
	int winner = 0;

	for (int i = 0; i < outputs.size(); i++)
	{
		if (outputs[i] > outputs[winner])
		{
			winner = i;
		}
	}
	
	// use switch statement to cast appropriate skill
	switch (winner)
	{
	case 0:
		castConsecration();
		break;

	case 1:
		castCrusaderStrike();
		break;

	case 2:
		castJudgment();
		break;

	case 3:
		castShieldOfRighteous();
		break;

	case 4:
		castAvengingWrath();
		break;

	case 5:
		castHolyShock();
		break;

	case 6:
		castHolyAvenger();
		break;

	case 7:
		castHolyPrism();
		break;

	case 8:
		castHammerOfWrath();
		break;

	case 9:
		castDreadFireVessel();
		break;

	case 10:
		castGlyphOfAssimilation();
		break;
	}
}

void Paladin::cycle()
{
	// handle gcd timer first before anything else
	if (gcdTimeLeft > 0)
	{
		gcdTimeLeft -= .1;

		if (gcdTimeLeft <= 0)
		{
			gcdTimeLeft = 0;
		}
	}

	// tic through consecration
	consecration();

	// go through crusader strikes recharge for each charge
	crusaderStrike();

	// cycle judgments cooldown if it needs to
	judgment();

	// for the internal cd of shield of righteous
	shieldOfRighteous();

	// avenging wrath cycles
	avengingWrath();

	// get the cd of holy shock down
	holyShock();

	// cooldown holy avengers 3 minute cd
	holyAvenger();

	// cooldown holy prism
	holyPrism();
	
	// hammer of wrath maintennance
	hammerOfWrath();

	// trinket cycle
	glyphOfAssimilation();

	// melee swings
	melee();
}