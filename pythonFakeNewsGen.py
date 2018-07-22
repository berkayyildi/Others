# -*- coding: latin-1 -*-
import random

names = ["Ali", "Veli", "Ahmet", "Ayse"]
surnames = ["Sparrow", "Swift", "Python", "Django"]

fakeNews = [
		"{} {}'da içinde bulunduğu {} kişiyi taşıyan uçak düştü".format(random.choice(names), random.choice(surnames), random.randint(0, 100)),
		"Cemiyetin ünlü izimlerinden {} {}, {} yıl hapis cezası istemiyle yargılanıcak.".format(random.choice(names), random.choice(surnames), random.randint(1, 50)),
	]

print random.choice(fakeNews)

