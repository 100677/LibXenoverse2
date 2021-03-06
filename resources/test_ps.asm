//
// Generated by Microsoft (R) D3DX9 Shader Compiler 9.15.779.0000
//
// Parameters:
//
//   sampler2D ImageSampler0;
//   bool g_bOutputGlareMRT_PS;
//   float4 g_vTone;
//
//
// Registers:
//
//   Name                 Reg   Size
//   -------------------- ----- ----
//   g_bOutputGlareMRT_PS b3       1
//   g_vTone              c48      1
//   ImageSampler0        s0       1
//

    ps_3_0
    def c0, 0, 0, 0, 0
    dcl_color_pp v0
    dcl_texcoord_pp v1.xy
    dcl_texcoord2_pp v2
    dcl_texcoord3_pp v3.xyz
    dcl_texcoord4_pp v4.w
    dcl_texcoord5_pp v5.w
    dcl_texcoord6_pp v6.xy
    dcl_texcoord7_pp v7.xyz
    dcl_2d s0
    mov_pp r2.xyz, v0
    mul_pp r1.xyz, r2, v3
    texld_pp r0, v1, s0
    mad_pp r2.xyz, v3, r2, r0
    mad_pp r1.xyz, r0, r1, -r2
    mad_pp r1.xyz, v6.x, r1, r2
    lrp_pp r2.xyz, v0.x, r1, r0
    mul_pp r0.w, r0.w, v4.w
    add_pp r1.xyz, r2, v2
    mul_pp r0.w, r0.w, v0.w
    mad_pp r0.xyz, r2, v2, -r1
    mul_pp r0.w, r0.w, v5.w
    mad_pp r1.xyz, v6.y, r0, r1
    mul_pp r1.w, r0.w, v2.w
    if b3
      mad_pp r0.xyz, r1, v7, -c48.w
      mul_pp r0.xyz, r0, c48
    else
      mov_pp r0.xyz, c0.x
    endif
    mov_pp r0.w, r1.w
    mov_pp oC0, r1
    mov_pp oC1, r0

// approximately 25 instruction slots used (1 texture, 24 arithmetic)
