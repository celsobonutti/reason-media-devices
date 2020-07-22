type t;

type track;

[@bs.send]
external getTracks: t => array(track) = "getTracks";