// a = [1, 2, 3]
// a.push(12)

// for (var c in a)
//     console.log(a[c]);

var str = "Visit W3CSchool!W3CSchool";
var substr = "W3CSchool";
var start = str.search(substr) + substr.length
start = str.substr(start).search("W3CSchool")
console.log(start)

var person=new Object();
person.firstname="John";
person.lastname="Doe";
person.age=50;
person.eyecolor="blue"; 
console.log(person.firstname + " is " + person.age + " years old.");
console.log(person)

person2={firstname:"John",lastname:"Doe",age:150,eyecolor:"blue"}; 
console.log(person2)