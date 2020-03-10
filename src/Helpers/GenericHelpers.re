open UiTypes;

/*
 * Bound a value within its upper and lower bounds. Works for int / float
 */
let bound = (lowerBound, upperBound, value) =>
  switch (value) {
  | value when value > upperBound => upperBound
  | value when value < lowerBound => lowerBound
  | _ => value
  };

/*
 * This function is used to add or subtract a percentate from any color
 * value. We take the percentage relative to 255 (max rgb value for any
 * given channel) and either add or subtract it.
 */
let operatePercent = (percentage, operation, value) => {
  let amount = 255 * percentage / 100;
  switch (operation) {
  | Add => value + amount
  | Subtract => value - amount
  };
};
