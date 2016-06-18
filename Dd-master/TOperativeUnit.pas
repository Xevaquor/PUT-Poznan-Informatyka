unit TOperativeUnit;

interface

type
	POperative = ^TOperative;
	TOperative = record
		FirstName : ShortString;
		LastName : ShortString;
		NickName : ShortString;
		DateOfBirth : TDateTime;
		BirthPlace : ShortString;
	end;

type TElemType = TOperative;
type PElemType = POperative;

type 
  PElem = ^TElem;
  TElem = record
    Val : TElemType;
    Next : PElem;
  end;

implementation

end.
