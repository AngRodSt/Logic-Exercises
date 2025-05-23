//Private Counter
function createCounter() {
  let count = 0;
  return function () {
    return count++;
  };
}
const counter = createCounter();

//Personalized Greater
function createGreeter(name) {
  return function (greeting = "Welcome") {
    return `${greeting}, ${name}`;
  };
}
const greeter = createGreeter("Sthefany");
greeter();

//Multiplier with factor and history
function createMultiplier(factor) {
  const history = [];
  return {
    multiply: (number) => {
      const result = number * factor;
      history.push(result);
      return result;
    },
    getHistory: () => [...history],
  };
}
const double = createMultiplier(2);
double.multiply(5);
double.getHistory();
