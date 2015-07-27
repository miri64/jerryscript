// Copyright 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

var person = {
    firstName:"John",
    lastName:"Doe",
    age:50,
    eyeColor:"blue",
    "gender":"male",
    0:0
};

assert (person.firstName === "John");
assert (person["firstName"] === "John");
assert (person.lastName === "Doe");
assert (person["lastName"] === "Doe");
assert (person.age === 50);
assert (person["age"] === 50);
assert (person.eyeColor === "blue");
assert (person["eyeColor"] === "blue");
assert (person.gender === "male");
assert (person["gender"] === "male");
assert (person["0"] === 0);

var x = person;
x.age = 40;
assert (x.age === 40);
assert (person.age === 40);

var john = new Object();
john.firstName = "John";
john.lastName = "Doe";
john.age = 40;
john.eyeColor = "blue";

assert (person.firstName === john.firstName);
assert (person.lastName === john.lastName);
assert (person.age === john.age);
assert (person.eyeColor === john.eyeColor);

var a, b; 
b = 'property1'; 
a = { 
  'property1' : 'value1', 
  get property2 () { return 1; }, 
  set property2 (a) {
    if (true)
      this.property3 = a * 10;
    else
      this.property3 = a;
  },
  set property3 (b) { this.property1 = b; }
}; 
assert (a.property1 === 'value1'); 
assert (a.property2 === 1); 
a.property3 = 'value2'; 
assert (a.property1 === 'value2'); 
a.property2 = 2.5; 
assert (a.property1 === 25); 
b = delete a[b]; 
assert (b === true); 
assert (a.property1 === undefined); 

flow = '';
a = {
  get q ()
  {
    flow += 'get: ' + (typeof q);

    return 0;
  },
  set q (v)
  {
    flow += ', set: ' + (typeof q);
  }
};

a.q;
a.q = 1;

assert (flow == 'get: undefined, set: undefined');

// FIXME: change to 'eval' after large object literals byte-code representation would be fixed (issue #276)
f = new Function("obj = { \
                 '1': '', '2': '', '3': '', '4': '', '5': '', '6': '', '7': '', '8': '', \
                 '9': '', '10': '', '11': '', '12': '', '13': '', '14': '', '15': '', '16': '', \
                 '17': '', '18': '', '19': '', '20': '', '21': '', '22': '', '23': '', '24': '', \
                 '25': '', '26': '', '27': '', '28': '', '29': '', '30': '', '31': '', '32': '', \
                 '33': '', '34': '', '35': '', '36': '', '37': '', '38': '', '39': '', '40': '', \
                 '41': '', '42': '', '43': '', '44': '', '45': '', '46': '', '47': '', '48': '', \
                 '49': '', '50': '', '51': '', '52': '', '53': '', '54': '', '55': '', '56': '', \
                 '57': '', '58': '', '59': '', '60': '', '61': '', '62': '', '63': '', '64': '', \
                 '65': '', '66': '', '67': '', '68': '', '69': '', '70': '', '71': '', '72': '', \
                 '73': '', '74': '', '75': '', '76': '', '77': '', '78': '', '79': '', '80': '', \
                 '81': '', '82': '', '83': '', '84': '', '85': '', '86': '', '87': '', '88': '', \
                 '89': '', '90': '', '91': '', '92': '', '93': '', '94': '', '95': '', '96': '', \
                 '97': '', '98': '', '99': '', '100': '', '101': '', '102': '', '103': '', '104': '', \
                 '105': '', '106': '', '107': '', '108': '', '109': '', '110': '', '111': '', '112': '', \
                 '113': '', '114': '', '115': '', '116': '', '117': '', '118': '', '119': '', '120': '', \
                 '121': '', '122': '', '123': '', '124': '', '125': '', '126': '', '127': '', '128': '', \
                 '129': '', '130': '', '131': '', '132': '', '133': '', '134': '', '135': '', '136': '', \
                 '137': '', '138': '', '139': '', '140': '', '141': '', '142': '', '143': '', '144': '', \
                 '145': '', '146': '', '147': '', '148': '', '149': '', '150': '', '151': '', '152': '', \
                 '153': '', '154': '', '155': '', '156': '', '157': '', '158': '', '159': '', '160': '', \
                 '161': '', '162': '', '163': '', '164': '', '165': '', '166': '', '167': '', '168': '', \
                 '169': '', '170': '', '171': '', '172': '', '173': '', '174': '', '175': '', '176': '', \
                 '177': '', '178': '', '179': '', '180': '', '181': '', '182': '', '183': '', '184': '', \
                 '185': '', '186': '', '187': '', '188': '', '189': '', '190': '', '191': '', '192': '', \
                 '193': '', '194': '', '195': '', '196': '', '197': '', '198': '', '199': '', '200': '', \
                 '201': '', '202': '', '203': '', '204': '', '205': '', '206': '', '207': '', '208': '', \
                 '209': '', '210': '', '211': '', '212': '', '213': '', '214': '', '215': '', '216': '', \
                 '217': '', '218': '', '219': '', '220': '', '221': '', '222': '', '223': '', '224': '', \
                 '225': '', '226': '', '227': '', '228': '', '229': '', '230': '', '231': '', '232': '', \
                 '233': '', '234': '', '235': '', '236': '', '237': '', '238': '', '239': '', '240': '', \
                 '241': '', '242': '', '243': '', '244': '', '245': '', '246': '', '247': '', '248': '', \
                 '249': '', '250': '', '251': '', '252': '', '253': '', '254': '', '255': '', \
                 '256': '', 257: '' };");