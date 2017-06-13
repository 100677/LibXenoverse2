//
// Generated by Microsoft (R) D3DX9 Shader Compiler 9.15.779.0000
//
// Parameters:
//
//   float4 g_GlareCoeff_VS;
//   float4 g_Incidence_VS;
//   float4 g_MaterialCol0_VS;
//   float4 g_MaterialCol1_VS;
//   float4 g_MaterialCol2_VS;
//   float4 g_MaterialCol3_VS;
//   float4 g_TexScroll0_VS;
//   float4 g_TexScroll1_VS;
//   bool g_bVersatile0_VS;
//   bool g_bVersatile1_VS;
//   bool g_bVersatile2_VS;
//   bool g_bVersatile3_VS;
//   float4x4 g_mWVP_VS;
//   float4x3 g_mWV_VS;
//   float4 g_vTexTile01_VS;
//
//
// Registers:
//
//   Name              Reg   Size
//   ----------------- ----- ----
//   g_bVersatile0_VS  b8       1
//   g_bVersatile1_VS  b9       1
//   g_bVersatile2_VS  b10      1
//   g_bVersatile3_VS  b11      1
//   g_mWVP_VS         c0       4
//   g_mWV_VS          c32      3
//   g_vTexTile01_VS   c43      1
//   g_TexScroll0_VS   c76      1
//   g_TexScroll1_VS   c77      1
//   g_MaterialCol0_VS c80      1
//   g_MaterialCol1_VS c81      1
//   g_MaterialCol2_VS c82      1
//   g_MaterialCol3_VS c83      1
//   g_Incidence_VS    c93      1
//   g_GlareCoeff_VS   c96      1
//

    vs_3_0
    def c4, 1, 0, -1, 0
    dcl_position v0
    dcl_normal v1
    dcl_texcoord v2
    dcl_color v3
    dcl_position o0
    dcl_color o1
    dcl_texcoord o2
    dcl_texcoord2 o3
    dcl_texcoord3 o4
    dcl_texcoord4 o5
    dcl_texcoord5 o6
    dcl_texcoord6 o7
    dcl_texcoord7 o8
    mad r0, v0.xyzx, c4.xxxy, c4.yyyx
    dp4 o0.w, r0, c3
    dp4 o0.x, r0, c0
    dp4 o0.y, r0, c1
    dp4 o0.z, r0, c2
    mov r0, c43
    mad r0.x, v2.x, r0.x, c76.x
    mad r0.y, v2.y, r0.y, -c76.y
    mad r0.z, v2.x, r0.z, c77.x
    mad r0.w, v2.y, r0.w, -c77.y
    if b11
      max r0, r0, c4.yzyz
      min o2, r0, c4.xyxy
    else
      mov o2, r0
    endif
    dp3 r0.x, v1, c32
    dp3 r0.y, v1, c33
    dp3 r0.z, v1, c34
    dp3 r0.w, r0, r0
    mov r1.xyz, c4
    add r0.y, r1.z, c80.w
    rsq r0.w, r0.w
    mad o5.w, v3.x, r0.y, c4.x
    mul r0.z, r0.z, r0.w
    add r0.y, r1.z, c93.x
    add_sat r0.w, r0_abs.z, c93.y
    mad_sat r1.w, r0_abs.z, c93.x, -r0.y
    mul r0.w, r0.w, r0.w
    mov r0.xyz, c83
    add r0.xyz, -r0, c82
    mul r0.w, r0.w, r0.w
    mad o3.xyz, r1.w, r0, c83
    mul o3.w, r0.w, r0.w
    if b8
      mov r0.x, c4.x
    else
      mov r0.x, c4.y
    endif
    if b9
      mov r0.y, c4.x
    else
      mov r0.y, c4.y
    endif
    if b10
      mov r0.z, c4.x
    else
      mov r0.z, c4.y
    endif
    mov r0.w, c4.y
    mov o7, r0
    mov o1, v3
    mov o4, c80
    mov o5.xyz, c4.y
    mul o6, r1.yyyx, c81.w
    mov o8, c96

// approximately 64 instruction slots used