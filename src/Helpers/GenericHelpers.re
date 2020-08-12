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

/*
 * When not providing an id for inputs with labels, we would still need to generate one.
 * We do this by re-using the labelstring in this case. There could be duplicates but this
 * will be caught by React and give a console output error. However, in 90% of the cases,
 * falling back to the label string will be just fine.
 */
let genIdentifier = (id, label) =>
  switch (id, label) {
  | (Some(idString), _) => idString
  | (None, Labeled(labelString)) => labelString
  | (None, Unlabeled) => ""
  };

/*
 * To aid the creation of random id's, we use UUID's v4 fn.
 */
[@bs.module "uuid"] [@bs.val] external v4: unit => string = "v4";
