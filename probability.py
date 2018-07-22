import random

"""
	Random Generator
	Written by Berkay YILDIZ
	 * 
	 * This program is free software: you can redistribute it and/or modify  
	 * it under the terms of the GNU General Public License as published by  
	 * the Free Software Foundation, version 3.
	 *
	 * This program is distributed in the hope that it will be useful, but 
	 * WITHOUT ANY WARRANTY; without even the implied warranty of 
	 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
	 * General Public License for more details.
	 *
	 * You should have received a copy of the GNU General Public License 
	 * along with this program. If not, see <http://www.gnu.org/licenses/>.
"""

def rollDice(num = 1):
	
	dices = []

	for i in range (0, num):
		dices.append(random.choice(range(1,7)))

	return dices



def tossCoin(num = 1):
	
	coins = []

	for i in range (0, num):
		coins.append(random.choice([True,False]))

	return coins


print (rollDice(2))
print (tossCoin(3))

