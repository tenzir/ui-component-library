const icons = require("react-icons/fi");
const fs = require("fs");
const os = require("os");

const mappedIcons = Object.keys(icons).map(icon => {
  const header = "Icon;\n";
  // Naively slice off two letters, just for removing 'Fi';
  let nameForReason = icon.slice(2, icon.length);
  return `module ${nameForReason} = {
  [@bs.module "react-icons/fi"] [@react.component]
  external make: (
    ~className: string=?,
    ~color: string=?,
    ~size: int=?,
    ~style: ReactDOMRe.Style.t=?
  ) => React.element = "${icon}";
};
`;
});

return fs.writeFileSync(`./src/Icons.re`, mappedIcons.join(""));
