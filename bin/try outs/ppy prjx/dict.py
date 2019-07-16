# create a mapping o state to abbreviation
states = {
    'Oregon' : 'OR',
    'Florida' : 'FL',
    'California' : 'CA',
    'New York' : 'NY',
    'Michigan' : 'MI'
}

#create a basic set of states and some cities in them
cities = {
    'CA' : 'San Fransico',
    'MI' : 'Detroit',
    'FL' : 'Jacksonville'
}

# add some more cities
cities['NY'] = 'New York'
cities['OR'] = 'Portland'

#print out some cities
print ("-" * 10)
print ("Michigan\'s abbreviation is :",states['Michigan'])
print ("Florida\'s abbreviation is:",states['Florida'])

print ('-' * 10)
print ("Michigan has:",cities[states['Michigan']])
print ("Florida has:",cities[states['Florida']])

#print state and abbreviation
print ('-' * 10)
for state, abbrev in states.items():
    print("%s is abbreviated as %s" %(state,abbrev))

#print every city in state
print ('-' * 10)
for state,abbrev in states.items():
    print(" %s state has %s" %(state,cities[abbrev]))

state = states.get('Texas')
if  not state:
    print ("Sorry, no Texas")

city = cities.get('TX','Does not exist')
print ("the city for state 'TX' is %s" %(city))
