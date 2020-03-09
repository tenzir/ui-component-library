open UiTypes;

let bound = (lowerBound, upperBound, value) =>
  switch (value) {
  | value when value > upperBound => upperBound
  | value when value < lowerBound => lowerBound
  | _ => value
  };

let operatePercent = (percentage, operation, value) => {
  let amount = 255 * percentage / 100;
  switch (operation) {
  | Add => value + amount
  | Subtract => value - amount
  };
};
