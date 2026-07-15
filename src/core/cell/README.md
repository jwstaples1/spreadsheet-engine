Structure Overview:

CellValue:
- ConstantValue (basic strings or numbers):
  + NumericValue (stored as float, can be formatted otherwise)
  + StringValue
	
- FormulaicValue (formulas that need to be evaluated)

--------

CellValue and ConstantValue are both virtual - ConstantValue serves more as an category class than a functional one, while CellValue passes virtual functions like "evaluate" and "toString"