//Exercise 1: Use __proto__ to assign prototypes in a way that any property lookup will follow the path: pockets → bed → table → head. For instance, pockets.pen should be 3 (found in table), and bed.glasses should be 1 (found in head)

let head = {
  glasses: 1,
};

let table = {
  pen: 3,
  __proto__: head,
};

let bed = {
  sheet: 1,
  pillow: 2,
  __proto__: table,
};

let pockets = {
  money: 2000,
  __proto__: bed,
};

console.log(bed.glasses);

//Exercise 2: We have rabbit inheriting from animal. If we call rabbit.eat(), which object receives the full property: animal or rabbit?
//Response: Rabbit receives the full property since we are using "this" which referce to the object before the doc

let animal = {
  eat() {
    this.full = true;
  },
};

let rabbit = {
  __proto__: animal,
};

rabbit.eat();

//Exercise 3 We have two hamsters: speedy and lazy inheriting from the general hamster object.
//When we feed one of them, the other one is also full. Why? How can we fix it?

//Response: This happens because as the eat function is called, is looking for the stomach property, since the inherence hamsters do not have it, the food is pushed into the prototype.
let hamster = {
  stomach: [],

  eat(food) {
    // this.stomach.push(food);
    this.stomach = [food]; //HERE THE CHANGE
  },
};

let speedy = {
  __proto__: hamster,
};

let lazy = {
  __proto__: hamster,
};

// This one found the food
speedy.eat("apple");
console.log(speedy.stomach); // apple

// This one also has it, why? fix please.
console.log(lazy.stomach); // apple
