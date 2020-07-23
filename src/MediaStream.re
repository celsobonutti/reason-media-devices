module Track = {
  type t;

  [@bs.send]
  external getConstraints: t => 'a = "getConstraints";
}

type t;

[@bs.send]
external getTracks: t => array(Track.t) = "getTracks";