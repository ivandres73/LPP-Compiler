#ifndef __LEXER_H__
#define __LEXER_H__

enum class StateId {
    Start_q0,
    Start_q1,
    BinHex_q0,
    BinHex_q1,
    BinHex_q2,
    Char_q0,
    Char_q1,
    Char_q3,
    Char_q5,
    Comments_q0,
    Comments_q1,
    Comments_q3,
    Comments_q4,
    Dec_q0,
    Iden_q0,
    KewA_q0,
    KewA_q1,
    KewA_q10,
    KewA_q12,
    KewA_q13,
    KewA_q14,
    KewA_q17,
    KewA_q18,
    KewA_q19,
    KewA_q2,
    KewA_q3,
    KewA_q4,
    KewA_q5,
    KewA_q7,
    KewA_q8,
    KewA_q9,
    KewB_q0,
    KewB_q1,
    KewB_q2,
    KewB_q3,
    KewB_q4,
    KewB_q5,
    KewB_q6,
    KewB_q7,
    KewC_q0,
    KewC_q1,
    KewC_q10,
    KewC_q12,
    KewC_q14,
    KewC_q16,
    KewC_q17,
    KewC_q18,
    KewC_q2,
    KewC_q20,
    KewC_q21,
    KewC_q23,
    KewC_q24,
    KewC_q25,
    KewC_q26,
    KewC_q27,
    KewC_q3,
    KewC_q4,
    KewC_q6,
    KewC_q7,
    KewC_q8,
    KewC_q9,
    KewD_q0,
    KewD_q1,
    KewD_q3,
    KewD_q4,
    KewE_q0,
    KewE_q1,
    KewE_q10,
    KewE_q11,
    KewE_q12,
    KewE_q13,
    KewE_q14,
    KewE_q16,
    KewE_q18,
    KewE_q19,
    KewE_q2,
    KewE_q20,
    KewE_q22,
    KewE_q25,
    KewE_q26,
    KewE_q27,
    KewE_q28,
    KewE_q29,
    KewE_q3,
    KewE_q4,
    KewE_q7,
    KewE_q8,
    KewE_q9,
    KewF_q0,
    KewF_q1,
    KewF_q10,
    KewF_q12,
    KewF_q13,
    KewF_q14,
    KewF_q17,
    KewF_q18,
    KewF_q19,
    KewF_q2,
    KewF_q3,
    KewF_q4,
    KewF_q6,
    KewF_q7,
    KewF_q8,
    KewH_q0,
    KewH_q1,
    KewH_q2,
    KewH_q4,
    KewH_q5,
    KewH_q7,
    KewH_q8,
    KewIden_q0,
    KewI_q0,
    KewI_q1,
    KewI_q2,
    KewI_q3,
    KewI_q4,
    KewI_q6,
    KewL_q0,
    KewL_q1,
    KewL_q10,
    KewL_q11,
    KewL_q12,
    KewL_q13,
    KewL_q16,
    KewL_q17,
    KewL_q18,
    KewL_q19,
    KewL_q2,
    KewL_q3,
    KewL_q4,
    KewL_q6,
    KewL_q8,
    KewM_q0,
    KewM_q1,
    KewM_q11,
    KewM_q2,
    KewM_q3,
    KewM_q4,
    KewM_q5,
    KewM_q6,
    KewM_q7,
    KewM_q9,
    KewN_q0,
    KewN_q2,
    KewO_q0,
    KewP_q0,
    KewP_q1,
    KewP_q10,
    KewP_q11,
    KewP_q12,
    KewP_q13,
    KewP_q14,
    KewP_q17,
    KewP_q18,
    KewP_q2,
    KewP_q4,
    KewP_q5,
    KewP_q6,
    KewP_q7,
    KewP_q8,
    KewP_q9,
    KewR_q0,
    KewR_q1,
    KewR_q10,
    KewR_q11,
    KewR_q13,
    KewR_q14,
    KewR_q16,
    KewR_q17,
    KewR_q18,
    KewR_q2,
    KewR_q20,
    KewR_q21,
    KewR_q22,
    KewR_q4,
    KewR_q5,
    KewR_q6,
    KewR_q8,
    KewR_q9,
    KewS_q0,
    KewS_q1,
    KewS_q10,
    KewS_q11,
    KewS_q12,
    KewS_q2,
    KewS_q3,
    KewS_q4,
    KewS_q5,
    KewS_q6,
    KewS_q7,
    KewS_q8,
    KewS_q9,
    KewT_q0,
    KewT_q1,
    KewT_q2,
    KewT_q3,
    KewV_q0,
    KewV_q1,
    KewV_q10,
    KewV_q11,
    KewV_q2,
    KewV_q4,
    KewV_q5,
    KewV_q6,
    KewV_q7,
    KewV_q8,
    KewV_q9,
    KewY_q0,
    Oper_q0,
    Oper_q15,
    Oper_q18,
    Oper_q20,
    Oper_q9,
    String_q0,
    String_q2,
};

enum class Token {
    Add,
    Assign,
    BinConst,
    CharConst,
    CloseBra,
    CloseParens,
    Colon,
    Comma,
    DecConst,
    EndFile,
    EqualTo,
    GreatEqual,
    GreatThan,
    HexConst,
    Iden,
    KwAbrir,
    KwArchivo,
    KwArreglo,
    KwBooleano,
    KwCadena,
    KwCaracter,
    KwCaso,
    KwCerrar,
    KwComo,
    KwDe,
    KwDiv,
    KwEntero,
    KwEntonces,
    KwEs,
    KwEscriba,
    KwEscribir,
    KwEscritura,
    KwFalso,
    KwFin,
    KwFinal,
    KwFuncion,
    KwHaga,
    KwHasta,
    KwInicio,
    KwLea,
    KwLectura,
    KwLeer,
    KwLlamar,
    KwMientras,
    KwMod,
    KwNo,
    KwO,
    KwPara,
    KwProcedimiento,
    KwReal,
    KwRegistro,
    KwRepita,
    KwRetorne,
    KwSecuencial,
    KwSi,
    KwSino,
    KwTipo,
    KwVar,
    KwVerdadero,
    KwY,
    LessEqual,
    LessThan,
    Mul,
    NotEqual,
    OpenParens,
    StringConst,
    Sub,
    Xor,
};
#endif