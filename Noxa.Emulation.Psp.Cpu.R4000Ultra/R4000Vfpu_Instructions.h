// ----------------------------------------------------------------------------
// PSP Player Emulation Suite
// Copyright (C) 2006 Ben Vanik (noxa)
// Licensed under the LGPL - see License.txt in the project root for details
// ----------------------------------------------------------------------------

#define DEFGEN( x )		bool x( R4000GenContext^ context, int address, uint code )
#define DEFIMPL( x )	int x( R4000Ctx* ctx, uint address, uint code )

DEFGEN( VfpuGenVPFX );
DEFGEN( VfpuGenLVS );
DEFGEN( VfpuGenLVQ );
DEFGEN( VfpuGenSVS );
DEFGEN( VfpuGenSVQ );
DEFGEN( VfpuGenMTV );
DEFGEN( VfpuGenMFV );
DEFGEN( VfpuGenVIIM );
DEFGEN( VfpuGenVFIM );
DEFIMPL( VfpuImplVSCL );
DEFIMPL( VfpuImplArith );

const VfpuInstruction _vfpuInstructions[] = {
{"bvf",			"?c,p",				0x49000000, 0xffe30000, VFPU_BRANCH,		VfpuGenDummy,		VfpuImplDummy		},
{"bvfl",		"?c,p",				0x49020000, 0xffe30000, VFPU_BRANCH_LIKELY,	VfpuGenDummy,		VfpuImplDummy		},
{"bvt",			"?c,p",				0x49010000, 0xffe30000, VFPU_BRANCH,		VfpuGenDummy,		VfpuImplDummy		},
{"bvtl",		"?c,p",				0x49030000, 0xffe30000, VFPU_BRANCH_LIKELY,	VfpuGenDummy,		VfpuImplDummy		},
{"lv.s",		"?m0x,?o(b)",		0xc8000000, 0xfc000000, VFPU_NORMAL,	VfpuGenLVS,			VfpuImplDummy		},
{"lv.q",		"?n3x,?o(b)",		0xd8000000, 0xfc000002, VFPU_NORMAL,	VfpuGenLVQ,			VfpuImplDummy		},
{"sv.s",		"?m0x,?o(b)",		0xe8000000, 0xfc000000, VFPU_NORMAL,	VfpuGenSVS,			VfpuImplDummy		},
{"sv.q",		"?n3x,?o(b),?z",	0xf8000000, 0xfc000000, VFPU_NORMAL,	VfpuGenSVQ,			VfpuImplDummy		},
{"vwb.q",		"?n3x,?o(b)",		0xf8000002, 0xfc000002, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"lvl.q",		"?n3x,?o(b)",		0xd4000000, 0xfc000002, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"lvr.q",		"?n3x,?o(b)",		0xd4000002, 0xfc000002, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"svl.q",		"?n3x,?o(b)",		0xf4000000, 0xfc000002, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"svr.q",		"?n3x,?o(b)",		0xf4000002, 0xfc000002, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"mtv",			"t,?d0z",			0x48e00000, 0xffe0ff80, VFPU_NORMAL,	VfpuGenMTV,			VfpuImplDummy		},
{"mfv",			"t,?d0z",			0x48600000, 0xffe0ff80, VFPU_NORMAL,	VfpuGenMFV,			VfpuImplDummy		},
{"mtvc",		"t,?q",				0x48e00000, 0xffe0ff00, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"mfvc",		"t,?q",				0x48600000, 0xffe0ff00, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmtvc",		"?q,?s0y",			0xd0510000, 0xffff8000, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmfvc",		"?d0z,?r",			0xd0500000, 0xffff0080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vadd.q",		"?d3d,?s3s,?t3t",	0x60008080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsub.q",		"?d3d,?s3s,?t3t",	0x60808080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vdiv.q",		"?x3z,?s3y,?t3x",	0x63808080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmul.q",		"?d3d,?s3s,?t3t",	0x64008080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vdot.q",		"?d0d,?s3s,?t3t",	0x64808080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vscl.q",		"?d3d,?s3s,?t0x",	0x65008080, 0xff808080, VFPU_PFX,		VfpuGenDummy,		VfpuImplVSCL		},
{"vhdp.q",		"?d0d,?s3y,?t3t",	0x66008080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmp.q",		"?f2,?s3s,?t3t",	0x6c008080, 0xff8080f0, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmin.q",		"?d3d,?s3s,?t3t",	0x6d008080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmax.q",		"?d3d,?s3s,?t3t",	0x6d808080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsgn.q",		"?d3d,?s3s",		0xd04a8080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcst.q",		"?d3d,?a",			0xd0608080, 0xffe0ff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vscmp.q",		"?d3d,?s3s,?t3t",	0x6e808080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsge.q",		"?d3d,?s3s,?t3t",	0x6f008080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vslt.q",		"?d3d,?s3s,?t3t",	0x6f808080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vi2uc.q",		"?d0m,?s3w",		0xd03c8080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vi2c.q",		"?d0m,?s3w",		0xd03d8080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vi2us.q",		"?d1m,?s3w",		0xd03e8080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vi2s.q",		"?d1m,?s3w",		0xd03f8080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmov.q",		"?d3d,?s3s",		0xd0008080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vabs.q",		"?d3d,?s3w",		0xd0018080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vneg.q",		"?d3d,?s3w",		0xd0028080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vidt.q",		"?d3d",				0xd0038080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsat0.q",		"?d3z,?s3s",		0xd0048080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsat1.q",		"?d3z,?s3s",		0xd0058080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vzero.q",		"?d3d",				0xd0068080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vone.q",		"?d3d",				0xd0078080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrcp.q",		"?x3z,?s3y",		0xd0108080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vrsq.q",		"?x3z,?s3y",		0xd0118080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsin.q",		"?x3z,?s3y",		0xd0128080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vcos.q",		"?x3z,?s3y",		0xd0138080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vexp2.q",		"?x3z,?s3y",		0xd0148080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vlog2.q",		"?x3z,?s3y",		0xd0158080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsqrt.q",		"?x3z,?s3y",		0xd0168080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vasin.q",		"?x3z,?s3y",		0xd0178080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vnrcp.q",		"?x3z,?s3y",		0xd0188080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vnsin.q",		"?x3z,?s3y",		0xd01a8080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrexp2.q",	"?x3z,?s3y",		0xd01c8080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrndi.q",		"?d3z",				0xd0218080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrndf1.q",	"?d3z",				0xd0228080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrndf2.q",	"?d3z",				0xd0238080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2h.q",		"?d1m,?s3s",		0xd0328080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsrt1.q",		"?d3d,?s3s",		0xd0408080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsrt2.q",		"?d3d,?s3s",		0xd0418080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsrt3.q",		"?d3d,?s3s",		0xd0488080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsrt4.q",		"?d3d,?s3s",		0xd0498080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vbfy1.q",		"?d3d,?s3s",		0xd0428080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vbfy2.q",		"?d3d,?s3s",		0xd0438080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vocp.q",		"?d3d,?s3y",		0xd0448080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vfad.q",		"?d0d,?s3s",		0xd0468080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vavg.q",		"?d0d,?s3s",		0xd0478080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2in.q",		"?d3m,?s3s,?b",		0xd2008080, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2iz.q",		"?d3m,?s3s,?b",		0xd2208080, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2iu.q",		"?d3m,?s3s,?b",		0xd2408080, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2id.q",		"?d3m,?s3s,?b",		0xd2608080, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vi2f.q",		"?d3d,?s3w,?b",		0xd2808080, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmovt.q",	"?d3d,?s3s,?e",		0xd2a08080, 0xfff88080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmovf.q",	"?d3d,?s3s,?e",		0xd2a88080, 0xfff88080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmmul.q",		"?v7z,?s7y,?t7x",	0xf0008080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vtfm4.q",		"?v3z,?s7y,?t3x",	0xf1808080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vhtfm4.q",	"?v3z,?s7y,?t3x",	0xf1808000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmscl.q",		"?x7z,?s7y,?t0x",	0xf2008080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vqmul.q",		"?v3z,?s3y,?t3x",	0xf2808080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmmov.q",		"?x7z,?s7y",		0xf3808080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmidt.q",		"?d7z",				0xf3838080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmzero.q",	"?d7z",				0xf3868080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmone.q",		"?d7z",				0xf3878080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrot.q",		"?x3z,?s0y,?w",		0xf3a08080, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vt4444.q",	"?d1z,?s3w",		0xd0598080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vt5551.q",	"?d1z,?s3w",		0xd05a8080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vt5650.q",	"?d1z,?s3w",		0xd05b8080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vadd.t",		"?d2d,?s2s,?t2t",	0x60008000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsub.t",		"?d2d,?s2s,?t2t",	0x60808000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vdiv.t",		"?x2z,?s2y,?t2x",	0x63808000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmul.t",		"?d2d,?s2s,?t2t",	0x64008000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vdot.t",		"?d0d,?s2s,?t2t",	0x64808000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vscl.t",		"?d2d,?s2s,?t0x",	0x65008000, 0xff808080, VFPU_PFX,		VfpuGenDummy,		VfpuImplVSCL		},
{"vhdp.t",		"?d0d,?s2y,?t2t",	0x66008000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcrs.t",		"?d2d,?s2y,?t2x",	0x66808000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmp.t",		"?f2,?s2s,?t2t",	0x6c008000, 0xff8080f0, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmp.t",		"?f1,?s2s",			0x6c008000, 0xffff80f0, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmp.t",		"?f0",				0x6c008000, 0xfffffff0, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmin.t",		"?d2d,?s2s,?t2t",	0x6d008000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmax.t",		"?d2d,?s2s,?t2t",	0x6d808000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsgn.t",		"?d2d,?s2s",		0xd04a8000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcst.t",		"?d2d,?a",			0xd0608000, 0xffe0ff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vscmp.t",		"?d2d,?s2s,?t2t",	0x6e808000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsge.t",		"?d2d,?s2s,?t2t",	0x6f008000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vslt.t",		"?d2d,?s2s,?t2t",	0x6f808000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmov.t",		"?d2d,?s2s",		0xd0008000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vabs.t",		"?d2d,?s2w",		0xd0018000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vneg.t",		"?d2d,?s2w",		0xd0028000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsat0.t",		"?d2z,?s2s",		0xd0048000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsat1.t",		"?d2z,?s2s",		0xd0058000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vzero.t",		"?d2d",				0xd0068000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vone.t",		"?d2d",				0xd0078000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrcp.t",		"?x2z,?s2y",		0xd0108000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vrsq.t",		"?x2z,?s2y",		0xd0118000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsin.t",		"?x2z,?s2y",		0xd0128000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vcos.t",		"?x2z,?s2y",		0xd0138000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vexp2.t",		"?x2z,?s2y",		0xd0148000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vlog2.t",		"?x2z,?s2y",		0xd0158000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsqrt.t",		"?x2z,?s2y",		0xd0168000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vasin.t",		"?x2z,?s2y",		0xd0178000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vnrcp.t",		"?x2z,?s2y",		0xd0188000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vnsin.t",		"?x2z,?s2y",		0xd01a8000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrexp2.t",	"?x2z,?s2y",		0xd01c8000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrndi.t",		"?d2z",				0xd0218000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrndf1.t",	"?d2z",				0xd0228000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrndf2.t",	"?d2z",				0xd0238000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vocp.t",		"?d2d,?s2y",		0xd0448000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vfad.t",		"?d0d,?s2s",		0xd0468000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vavg.t",		"?d0d,?s2s",		0xd0478000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2in.t",		"?d2m,?s2s,?b",		0xd2008000, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2iz.t",		"?d2m,?s2s,?b",		0xd2208000, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2iu.t",		"?d2m,?s2s,?b",		0xd2408000, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2id.t",		"?d2m,?s2s,?b",		0xd2608000, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vi2f.t",		"?d2d,?s2w,?b",		0xd2808000, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmovt.t",	"?d2d,?s2s,?e",		0xd2a08000, 0xfff88080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmovf.t",	"?d2d,?s2s,?e",		0xd2a88000, 0xfff88080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmmul.t",		"?v6z,?s6y,?t6x",	0xf0008000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vtfm3.t",		"?v2z,?s6y,?t2x",	0xf1008000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vhtfm3.t",	"?v2z,?s6y,?t2x",	0xf1000080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmscl.t",		"?x6z,?s6y,?t0x",	0xf2008000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmmov.t",		"?x6z,?s6y",		0xf3808000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmidt.t",		"?d6z",				0xf3838000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmzero.t",	"?d6z",				0xf3868000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmone.t",		"?d6z",				0xf3878000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrot.t",		"?x2z,?s0y,?w",		0xf3a08000, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcrsp.t",		"?d2z,?s2y,?t2x",	0xf2808000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vadd.p",		"?d1d,?s1s,?t1t",	0x60000080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsub.p",		"?d1d,?s1s,?t1t",	0x60800080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vdiv.p",		"?x1z,?s1y,?t1x",	0x63800080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmul.p",		"?d1d,?s1s,?t1t",	0x64000080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vdot.p",		"?d0d,?s1s,?t1t",	0x64800080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vscl.p",		"?d1d,?s1s,?t0x",	0x65000080, 0xff808080, VFPU_PFX,		VfpuGenDummy,		VfpuImplVSCL		},
{"vhdp.p",		"?d0d,?s1y,?t1t",	0x66000080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vdet.p",		"?d0d,?s1s,?t1x",	0x67000080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmp.p",		"?f2,?s1s,?t1t",	0x6c000080, 0xff8080f0, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmin.p",		"?d1d,?s1s,?t1t",	0x6d000080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmax.p",		"?d1d,?s1s,?t1t",	0x6d800080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsgn.p",		"?d1d,?s1s",		0xd04a0080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcst.p",		"?d1d,?a",			0xd0600080, 0xffe0ff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vscmp.p",		"?d1d,?s1s,?t1t",	0x6e800080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsge.p",		"?d1d,?s1s,?t1t",	0x6f000080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vslt.p",		"?d1d,?s1s,?t1t",	0x6f800080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vus2i.p",		"?d3m,?s1y",		0xd03a0080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vs2i.p",		"?d3m,?s1y",		0xd03b0080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vi2us.p",		"?d0m,?s1w",		0xd03e0080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vi2s.p",		"?d0m,?s1w",		0xd03f0080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmov.p",		"?d1d,?s1s",		0xd0000080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vabs.p",		"?d1d,?s1w",		0xd0010080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vneg.p",		"?d1d,?s1w",		0xd0020080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vidt.p",		"?d1d",				0xd0030080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsat0.p",		"?d1z,?s1s",		0xd0040080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsat1.p",		"?d1z,?s1s",		0xd0050080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vzero.p",		"?d1d",				0xd0060080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vone.p",		"?d1d",				0xd0070080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrcp.p",		"?x1z,?s1y",		0xd0100080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vrsq.p",		"?x1z,?s1y",		0xd0110080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsin.p",		"?x1z,?s1y",		0xd0120080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vcos.p",		"?x1z,?s1y",		0xd0130080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vexp2.p",		"?x1z,?s1y",		0xd0140080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vlog2.p",		"?x1z,?s1y",		0xd0150080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsqrt.p",		"?x1z,?s1y",		0xd0160080, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vasin.p",		"?x1z,?s1y",		0xd0170080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vnrcp.p",		"?x1z,?s1y",		0xd0180080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vnsin.p",		"?x1z,?s1y",		0xd01a0080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrexp2.p",	"?x1z,?s1y",		0xd01c0080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrndi.p",		"?d1z",				0xd0210080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrndf1.p",	"?d1z",				0xd0220080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrndf2.p",	"?d1z",				0xd0230080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2h.p",		"?d0m,?s1s",		0xd0320080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vh2f.p",		"?d3d,?s1y",		0xd0330080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vbfy1.p",		"?d1d,?s1s",		0xd0420080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vocp.p",		"?d1d,?s1y",		0xd0440080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsocp.p",		"?d3z,?s1y",		0xd0450080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vfad.p",		"?d0d,?s1s",		0xd0460080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vavg.p",		"?d0d,?s1s",		0xd0470080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2in.p",		"?d1m,?s1s,?b",		0xd2000080, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2iz.p",		"?d1m,?s1s,?b",		0xd2200080, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2iu.p",		"?d1m,?s1s,?b",		0xd2400080, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2id.p",		"?d1m,?s1s,?b",		0xd2600080, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vi2f.p",		"?d1d,?s1w,?b",		0xd2800080, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmovt.p",	"?d1d,?s1s,?e",		0xd2a00080, 0xfff88080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmovf.p",	"?d1d,?s1s,?e",		0xd2a80080, 0xfff88080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmmul.p",		"?v5z,?s5y,?t5x",	0xf0000080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vtfm2.p",		"?v1z,?s5y,?t1x",	0xf0800080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vhtfm2.p",	"?v1z,?s5y,?t1x",	0xf0800000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmscl.p",		"?x5z,?s5y,?t0x",	0xf2000080, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmmov.p",		"?x5z,?s5y",		0xf3800080, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmidt.p",		"?d5z",				0xf3830080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmzero.p",	"?d5z",				0xf3860080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmone.p",		"?d5z",				0xf3870080, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrot.p",		"?x1z,?s0y,?w",		0xf3a00080, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vadd.s",		"?d0d,?s0s,?t0t",	0x60000000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsub.s",		"?d0d,?s0s,?t0t",	0x60800000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vdiv.s",		"?x0d,?s0s,?t0t",	0x63800000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmul.s",		"?d0d,?s0s,?t0t",	0x64000000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmp.s",		"?f2,?s0s,?t0t",	0x6c000000, 0xff8080f0, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmin.s",		"?d0d,?s0s,?t0t",	0x6d000000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmax.s",		"?d0d,?s0s,?t0t",	0x6d800000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsgn.s",		"?d0d,?s0s",		0xd04a0000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcst.s",		"?d0d,?a",			0xd0600000, 0xffe0ff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vscmp.s",		"?d0d,?s0s,?t0t",	0x6e800000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsge.s",		"?d0d,?s0s,?t0t",	0x6f000000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vslt.s",		"?d0d,?s0s,?t0t",	0x6f800000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vus2i.s",		"?d1m,?s0y",		0xd03a0000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vs2i.s",		"?d1m,?s0y",		0xd03b0000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vmov.s",		"?d0d,?s0s",		0xd0000000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vabs.s",		"?d0d,?s0w",		0xd0010000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vneg.s",		"?d0d,?s0w",		0xd0020000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsat0.s",		"?d0z,?s0s",		0xd0040000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsat1.s",		"?d0z,?s0s",		0xd0050000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vzero.s",		"?d0d",				0xd0060000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vone.s",		"?d0d",				0xd0070000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrcp.s",		"?x0d,?s0s",		0xd0100000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vrsq.s",		"?x0d,?s0s",		0xd0110000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsin.s",		"?x0d,?s0s",		0xd0120000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vcos.s",		"?x0d,?s0s",		0xd0130000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vexp2.s",		"?x0d,?s0s",		0xd0140000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vlog2.s",		"?x0d,?s0s",		0xd0150000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vsqrt.s",		"?x0d,?s0s",		0xd0160000, 0xffff8080, VFPU_PFX,		VfpuGenDummy,		VfpuImplArith		},
{"vasin.s",		"?x0d,?s0s",		0xd0170000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vnrcp.s",		"?x0d,?s0y",		0xd0180000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vnsin.s",		"?x0d,?s0y",		0xd01a0000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrexp2.s",	"?x0d,?s0y",		0xd01c0000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrnds.s",		"?s0y",				0xd0200000, 0xffff80ff, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrndi.s",		"?d0d",				0xd0210000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrndf1.s",	"?d0d",				0xd0220000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vrndf2.s",	"?d0d",				0xd0230000, 0xffffff80, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vh2f.s",		"?d1d,?s0y",		0xd0330000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsbz.s",		"?d0d,?s0s",		0xd0360000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsbn.s",		"?d0d,?s0s,?t0t",	0x61000000, 0xff808080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vlgb.s",		"?d0d,?s0s",		0xd0370000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vocp.s",		"?d0d,?s0y",		0xd0440000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsocp.s",		"?d1z,?s0y",		0xd0450000, 0xffff8080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2in.s",		"?d0m,?s0s,?b",		0xd2000000, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2iz.s",		"?d0m,?s0s,?b",		0xd2200000, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2iu.s",		"?d0m,?s0s,?b",		0xd2400000, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vf2id.s",		"?d0m,?s0s,?b",		0xd2600000, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vi2f.s",		"?d0d,?s0w,?b",		0xd2800000, 0xffe08080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmovt.s",	"?d0d,?s0s,?e",		0xd2a00000, 0xfff88080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vcmovf.s",	"?d0d,?s0s,?e",		0xd2a80000, 0xfff88080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vwbn.s",		"?d0d,?s0s,?i",		0xd3000000, 0xff008080, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vpfxs",		"?0,?1,?2,?3",		0xdc000000, 0xff000000, VFPU_NORMAL,	VfpuGenVPFX,		VfpuImplDummy		},
{"vpfxt",		"?0,?1,?2,?3",		0xdd000000, 0xff000000, VFPU_NORMAL,	VfpuGenVPFX,		VfpuImplDummy		},
{"vpfxd",		"?4,?5,?6,?7",		0xde000000, 0xff000000, VFPU_NORMAL,	VfpuGenVPFX,		VfpuImplDummy		},
{"viim.s",		"?t0d,j",			0xdf000000, 0xff800000, VFPU_PFX,		VfpuGenVIIM,		VfpuImplDummy		},
{"vfim.s",		"?t0d,?u",			0xdf800000, 0xff800000, VFPU_PFX,		VfpuGenVFIM,		VfpuImplDummy		},
{"vnop",		"",					0xffff0000, 0xffffffff, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vflush",		"",					0xffff040d, 0xffffffff, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsync",		"",					0xffff0320, 0xffffffff, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
{"vsync",		"i",				0xffff0000, 0xffff0000, VFPU_NORMAL,	VfpuGenDummy,		VfpuImplDummy		},
};

const int _vfpuNumInstructions = sizeof( _vfpuInstructions ) / sizeof( VfpuInstruction );