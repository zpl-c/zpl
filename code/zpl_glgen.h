/*

ZPL - GLGEN module

Usage:
  #define ZPL_GLGEN_IMPLEMENTATION exactly in ONE source file right BEFORE including the library, like:

  #define ZPL_GLGEN_IMPLEMENTATION
  #include"zpl_glgen.h"

  Other files include just the header file.

Credits:
  See AUTHORS.md

GitHub:
  https://github.com/zpl-c/zpl

Version History:
  1.1.0 - Added support for the latest glcorearb.h standard format
  1.0.0 - Initial version

  This Software is dual licensed under the following licenses:

  Unlicense
  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.

  For more information, please refer to <http://unlicense.org/>

  Apache 2.0
  Copyright 2017-2018 Dominik Madarász <zaklaus@outlook.com>
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
    
      http://www.apache.org/licenses/LICENSE-2.0
    
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License. 

*/

#ifndef ZPL_INCLUDE_ZPL_GLGEN_H
#define ZPL_INCLUDE_ZPL_GLGEN_H

#include "glcorearb.h"

#ifndef __gl_h_
#define __gl_h_
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*zpl_gl3WglProc)(void);

/* glgen api */
int zpl_glgen_init(void);
int zpl_glgen_is_supported(int major, int minor);
zpl_gl3WglProc zpl_glgen_get_proc_address(char const *proc);

/* OpenGL functions */
extern PFNGLACTIVEPROGRAMEXTPROC                            glgenActiveProgramEXT;
extern PFNGLACTIVESHADERPROGRAMPROC                         glgenActiveShaderProgram;
extern PFNGLACTIVETEXTUREPROC                               glgenActiveTexture;
extern PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC         glgenApplyFramebufferAttachmentCMAAINTEL;
extern PFNGLATTACHSHADERPROC                                glgenAttachShader;
extern PFNGLBEGINCONDITIONALRENDERPROC                      glgenBeginConditionalRender;
extern PFNGLBEGINCONDITIONALRENDERNVPROC                    glgenBeginConditionalRenderNV;
extern PFNGLBEGINPERFMONITORAMDPROC                         glgenBeginPerfMonitorAMD;
extern PFNGLBEGINPERFQUERYINTELPROC                         glgenBeginPerfQueryINTEL;
extern PFNGLBEGINQUERYPROC                                  glgenBeginQuery;
extern PFNGLBEGINQUERYINDEXEDPROC                           glgenBeginQueryIndexed;
extern PFNGLBEGINTRANSFORMFEEDBACKPROC                      glgenBeginTransformFeedback;
extern PFNGLBINDATTRIBLOCATIONPROC                          glgenBindAttribLocation;
extern PFNGLBINDBUFFERPROC                                  glgenBindBuffer;
extern PFNGLBINDBUFFERBASEPROC                              glgenBindBufferBase;
extern PFNGLBINDBUFFERRANGEPROC                             glgenBindBufferRange;
extern PFNGLBINDBUFFERSBASEPROC                             glgenBindBuffersBase;
extern PFNGLBINDBUFFERSRANGEPROC                            glgenBindBuffersRange;
extern PFNGLBINDFRAGDATALOCATIONPROC                        glgenBindFragDataLocation;
extern PFNGLBINDFRAGDATALOCATIONINDEXEDPROC                 glgenBindFragDataLocationIndexed;
extern PFNGLBINDFRAMEBUFFERPROC                             glgenBindFramebuffer;
extern PFNGLBINDIMAGETEXTUREPROC                            glgenBindImageTexture;
extern PFNGLBINDIMAGETEXTURESPROC                           glgenBindImageTextures;
extern PFNGLBINDMULTITEXTUREEXTPROC                         glgenBindMultiTextureEXT;
extern PFNGLBINDPROGRAMPIPELINEPROC                         glgenBindProgramPipeline;
extern PFNGLBINDRENDERBUFFERPROC                            glgenBindRenderbuffer;
extern PFNGLBINDSAMPLERPROC                                 glgenBindSampler;
extern PFNGLBINDSAMPLERSPROC                                glgenBindSamplers;
extern PFNGLBINDSHADINGRATEIMAGENVPROC                      glgenBindShadingRateImageNV;
extern PFNGLBINDTEXTUREPROC                                 glgenBindTexture;
extern PFNGLBINDTEXTUREUNITPROC                             glgenBindTextureUnit;
extern PFNGLBINDTEXTURESPROC                                glgenBindTextures;
extern PFNGLBINDTRANSFORMFEEDBACKPROC                       glgenBindTransformFeedback;
extern PFNGLBINDVERTEXARRAYPROC                             glgenBindVertexArray;
extern PFNGLBINDVERTEXBUFFERPROC                            glgenBindVertexBuffer;
extern PFNGLBINDVERTEXBUFFERSPROC                           glgenBindVertexBuffers;
extern PFNGLBLENDBARRIERKHRPROC                             glgenBlendBarrierKHR;
extern PFNGLBLENDBARRIERNVPROC                              glgenBlendBarrierNV;
extern PFNGLBLENDCOLORPROC                                  glgenBlendColor;
extern PFNGLBLENDEQUATIONPROC                               glgenBlendEquation;
extern PFNGLBLENDEQUATIONSEPARATEPROC                       glgenBlendEquationSeparate;
extern PFNGLBLENDEQUATIONSEPARATEIPROC                      glgenBlendEquationSeparatei;
extern PFNGLBLENDEQUATIONSEPARATEIARBPROC                   glgenBlendEquationSeparateiARB;
extern PFNGLBLENDEQUATIONIPROC                              glgenBlendEquationi;
extern PFNGLBLENDEQUATIONIARBPROC                           glgenBlendEquationiARB;
extern PFNGLBLENDFUNCPROC                                   glgenBlendFunc;
extern PFNGLBLENDFUNCSEPARATEPROC                           glgenBlendFuncSeparate;
extern PFNGLBLENDFUNCSEPARATEIPROC                          glgenBlendFuncSeparatei;
extern PFNGLBLENDFUNCSEPARATEIARBPROC                       glgenBlendFuncSeparateiARB;
extern PFNGLBLENDFUNCIPROC                                  glgenBlendFunci;
extern PFNGLBLENDFUNCIARBPROC                               glgenBlendFunciARB;
extern PFNGLBLENDPARAMETERINVPROC                           glgenBlendParameteriNV;
extern PFNGLBLITFRAMEBUFFERPROC                             glgenBlitFramebuffer;
extern PFNGLBLITNAMEDFRAMEBUFFERPROC                        glgenBlitNamedFramebuffer;
extern PFNGLBUFFERADDRESSRANGENVPROC                        glgenBufferAddressRangeNV;
extern PFNGLBUFFERATTACHMEMORYNVPROC                        glgenBufferAttachMemoryNV;
extern PFNGLBUFFERDATAPROC                                  glgenBufferData;
extern PFNGLBUFFERPAGECOMMITMENTARBPROC                     glgenBufferPageCommitmentARB;
extern PFNGLBUFFERSTORAGEPROC                               glgenBufferStorage;
extern PFNGLBUFFERSUBDATAPROC                               glgenBufferSubData;
extern PFNGLCALLCOMMANDLISTNVPROC                           glgenCallCommandListNV;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC                      glgenCheckFramebufferStatus;
extern PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC                 glgenCheckNamedFramebufferStatus;
extern PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC              glgenCheckNamedFramebufferStatusEXT;
extern PFNGLCLAMPCOLORPROC                                  glgenClampColor;
extern PFNGLCLEARPROC                                       glgenClear;
extern PFNGLCLEARBUFFERDATAPROC                             glgenClearBufferData;
extern PFNGLCLEARBUFFERSUBDATAPROC                          glgenClearBufferSubData;
extern PFNGLCLEARBUFFERFIPROC                               glgenClearBufferfi;
extern PFNGLCLEARBUFFERFVPROC                               glgenClearBufferfv;
extern PFNGLCLEARBUFFERIVPROC                               glgenClearBufferiv;
extern PFNGLCLEARBUFFERUIVPROC                              glgenClearBufferuiv;
extern PFNGLCLEARCOLORPROC                                  glgenClearColor;
extern PFNGLCLEARDEPTHPROC                                  glgenClearDepth;
extern PFNGLCLEARDEPTHFPROC                                 glgenClearDepthf;
extern PFNGLCLEARNAMEDBUFFERDATAPROC                        glgenClearNamedBufferData;
extern PFNGLCLEARNAMEDBUFFERDATAEXTPROC                     glgenClearNamedBufferDataEXT;
extern PFNGLCLEARNAMEDBUFFERSUBDATAPROC                     glgenClearNamedBufferSubData;
extern PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC                  glgenClearNamedBufferSubDataEXT;
extern PFNGLCLEARNAMEDFRAMEBUFFERFIPROC                     glgenClearNamedFramebufferfi;
extern PFNGLCLEARNAMEDFRAMEBUFFERFVPROC                     glgenClearNamedFramebufferfv;
extern PFNGLCLEARNAMEDFRAMEBUFFERIVPROC                     glgenClearNamedFramebufferiv;
extern PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC                    glgenClearNamedFramebufferuiv;
extern PFNGLCLEARSTENCILPROC                                glgenClearStencil;
extern PFNGLCLEARTEXIMAGEPROC                               glgenClearTexImage;
extern PFNGLCLEARTEXSUBIMAGEPROC                            glgenClearTexSubImage;
extern PFNGLCLIENTATTRIBDEFAULTEXTPROC                      glgenClientAttribDefaultEXT;
extern PFNGLCLIENTWAITSYNCPROC                              glgenClientWaitSync;
extern PFNGLCLIPCONTROLPROC                                 glgenClipControl;
extern PFNGLCOLORFORMATNVPROC                               glgenColorFormatNV;
extern PFNGLCOLORMASKPROC                                   glgenColorMask;
extern PFNGLCOLORMASKIPROC                                  glgenColorMaski;
extern PFNGLCOMMANDLISTSEGMENTSNVPROC                       glgenCommandListSegmentsNV;
extern PFNGLCOMPILECOMMANDLISTNVPROC                        glgenCompileCommandListNV;
extern PFNGLCOMPILESHADERPROC                               glgenCompileShader;
extern PFNGLCOMPILESHADERINCLUDEARBPROC                     glgenCompileShaderIncludeARB;
extern PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC                glgenCompressedMultiTexImage1DEXT;
extern PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC                glgenCompressedMultiTexImage2DEXT;
extern PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC                glgenCompressedMultiTexImage3DEXT;
extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC             glgenCompressedMultiTexSubImage1DEXT;
extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC             glgenCompressedMultiTexSubImage2DEXT;
extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC             glgenCompressedMultiTexSubImage3DEXT;
extern PFNGLCOMPRESSEDTEXIMAGE1DPROC                        glgenCompressedTexImage1D;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC                        glgenCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXIMAGE3DPROC                        glgenCompressedTexImage3D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC                     glgenCompressedTexSubImage1D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC                     glgenCompressedTexSubImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC                     glgenCompressedTexSubImage3D;
extern PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC                 glgenCompressedTextureImage1DEXT;
extern PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC                 glgenCompressedTextureImage2DEXT;
extern PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC                 glgenCompressedTextureImage3DEXT;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC                 glgenCompressedTextureSubImage1D;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC              glgenCompressedTextureSubImage1DEXT;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC                 glgenCompressedTextureSubImage2D;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC              glgenCompressedTextureSubImage2DEXT;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC                 glgenCompressedTextureSubImage3D;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC              glgenCompressedTextureSubImage3DEXT;
extern PFNGLCONSERVATIVERASTERPARAMETERFNVPROC              glgenConservativeRasterParameterfNV;
extern PFNGLCONSERVATIVERASTERPARAMETERINVPROC              glgenConservativeRasterParameteriNV;
extern PFNGLCOPYBUFFERSUBDATAPROC                           glgenCopyBufferSubData;
extern PFNGLCOPYIMAGESUBDATAPROC                            glgenCopyImageSubData;
extern PFNGLCOPYMULTITEXIMAGE1DEXTPROC                      glgenCopyMultiTexImage1DEXT;
extern PFNGLCOPYMULTITEXIMAGE2DEXTPROC                      glgenCopyMultiTexImage2DEXT;
extern PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC                   glgenCopyMultiTexSubImage1DEXT;
extern PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC                   glgenCopyMultiTexSubImage2DEXT;
extern PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC                   glgenCopyMultiTexSubImage3DEXT;
extern PFNGLCOPYNAMEDBUFFERSUBDATAPROC                      glgenCopyNamedBufferSubData;
extern PFNGLCOPYPATHNVPROC                                  glgenCopyPathNV;
extern PFNGLCOPYTEXIMAGE1DPROC                              glgenCopyTexImage1D;
extern PFNGLCOPYTEXIMAGE2DPROC                              glgenCopyTexImage2D;
extern PFNGLCOPYTEXSUBIMAGE1DPROC                           glgenCopyTexSubImage1D;
extern PFNGLCOPYTEXSUBIMAGE2DPROC                           glgenCopyTexSubImage2D;
extern PFNGLCOPYTEXSUBIMAGE3DPROC                           glgenCopyTexSubImage3D;
extern PFNGLCOPYTEXTUREIMAGE1DEXTPROC                       glgenCopyTextureImage1DEXT;
extern PFNGLCOPYTEXTUREIMAGE2DEXTPROC                       glgenCopyTextureImage2DEXT;
extern PFNGLCOPYTEXTURESUBIMAGE1DPROC                       glgenCopyTextureSubImage1D;
extern PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC                    glgenCopyTextureSubImage1DEXT;
extern PFNGLCOPYTEXTURESUBIMAGE2DPROC                       glgenCopyTextureSubImage2D;
extern PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC                    glgenCopyTextureSubImage2DEXT;
extern PFNGLCOPYTEXTURESUBIMAGE3DPROC                       glgenCopyTextureSubImage3D;
extern PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC                    glgenCopyTextureSubImage3DEXT;
extern PFNGLCOVERFILLPATHINSTANCEDNVPROC                    glgenCoverFillPathInstancedNV;
extern PFNGLCOVERFILLPATHNVPROC                             glgenCoverFillPathNV;
extern PFNGLCOVERSTROKEPATHINSTANCEDNVPROC                  glgenCoverStrokePathInstancedNV;
extern PFNGLCOVERSTROKEPATHNVPROC                           glgenCoverStrokePathNV;
extern PFNGLCOVERAGEMODULATIONNVPROC                        glgenCoverageModulationNV;
extern PFNGLCOVERAGEMODULATIONTABLENVPROC                   glgenCoverageModulationTableNV;
extern PFNGLCREATEBUFFERSPROC                               glgenCreateBuffers;
extern PFNGLCREATECOMMANDLISTSNVPROC                        glgenCreateCommandListsNV;
extern PFNGLCREATEFRAMEBUFFERSPROC                          glgenCreateFramebuffers;
extern PFNGLCREATEPERFQUERYINTELPROC                        glgenCreatePerfQueryINTEL;
extern PFNGLCREATEPROGRAMPROC                               glgenCreateProgram;
extern PFNGLCREATEPROGRAMPIPELINESPROC                      glgenCreateProgramPipelines;
extern PFNGLCREATEQUERIESPROC                               glgenCreateQueries;
extern PFNGLCREATERENDERBUFFERSPROC                         glgenCreateRenderbuffers;
extern PFNGLCREATESAMPLERSPROC                              glgenCreateSamplers;
extern PFNGLCREATESHADERPROC                                glgenCreateShader;
extern PFNGLCREATESHADERPROGRAMEXTPROC                      glgenCreateShaderProgramEXT;
extern PFNGLCREATESHADERPROGRAMVPROC                        glgenCreateShaderProgramv;
extern PFNGLCREATESTATESNVPROC                              glgenCreateStatesNV;
extern PFNGLCREATESYNCFROMCLEVENTARBPROC                    glgenCreateSyncFromCLeventARB;
extern PFNGLCREATETEXTURESPROC                              glgenCreateTextures;
extern PFNGLCREATETRANSFORMFEEDBACKSPROC                    glgenCreateTransformFeedbacks;
extern PFNGLCREATEVERTEXARRAYSPROC                          glgenCreateVertexArrays;
extern PFNGLCULLFACEPROC                                    glgenCullFace;
extern PFNGLDEBUGMESSAGECALLBACKPROC                        glgenDebugMessageCallback;
extern PFNGLDEBUGMESSAGECALLBACKARBPROC                     glgenDebugMessageCallbackARB;
extern PFNGLDEBUGMESSAGECONTROLPROC                         glgenDebugMessageControl;
extern PFNGLDEBUGMESSAGECONTROLARBPROC                      glgenDebugMessageControlARB;
extern PFNGLDEBUGMESSAGEINSERTPROC                          glgenDebugMessageInsert;
extern PFNGLDEBUGMESSAGEINSERTARBPROC                       glgenDebugMessageInsertARB;
extern PFNGLDELETEBUFFERSPROC                               glgenDeleteBuffers;
extern PFNGLDELETECOMMANDLISTSNVPROC                        glgenDeleteCommandListsNV;
extern PFNGLDELETEFRAMEBUFFERSPROC                          glgenDeleteFramebuffers;
extern PFNGLDELETENAMEDSTRINGARBPROC                        glgenDeleteNamedStringARB;
extern PFNGLDELETEPATHSNVPROC                               glgenDeletePathsNV;
extern PFNGLDELETEPERFMONITORSAMDPROC                       glgenDeletePerfMonitorsAMD;
extern PFNGLDELETEPERFQUERYINTELPROC                        glgenDeletePerfQueryINTEL;
extern PFNGLDELETEPROGRAMPROC                               glgenDeleteProgram;
extern PFNGLDELETEPROGRAMPIPELINESPROC                      glgenDeleteProgramPipelines;
extern PFNGLDELETEQUERIESPROC                               glgenDeleteQueries;
extern PFNGLDELETERENDERBUFFERSPROC                         glgenDeleteRenderbuffers;
extern PFNGLDELETESAMPLERSPROC                              glgenDeleteSamplers;
extern PFNGLDELETESHADERPROC                                glgenDeleteShader;
extern PFNGLDELETESTATESNVPROC                              glgenDeleteStatesNV;
extern PFNGLDELETESYNCPROC                                  glgenDeleteSync;
extern PFNGLDELETETEXTURESPROC                              glgenDeleteTextures;
extern PFNGLDELETETRANSFORMFEEDBACKSPROC                    glgenDeleteTransformFeedbacks;
extern PFNGLDELETEVERTEXARRAYSPROC                          glgenDeleteVertexArrays;
extern PFNGLDEPTHFUNCPROC                                   glgenDepthFunc;
extern PFNGLDEPTHMASKPROC                                   glgenDepthMask;
extern PFNGLDEPTHRANGEPROC                                  glgenDepthRange;
extern PFNGLDEPTHRANGEARRAYVPROC                            glgenDepthRangeArrayv;
extern PFNGLDEPTHRANGEINDEXEDPROC                           glgenDepthRangeIndexed;
extern PFNGLDEPTHRANGEFPROC                                 glgenDepthRangef;
extern PFNGLDETACHSHADERPROC                                glgenDetachShader;
extern PFNGLDISABLEPROC                                     glgenDisable;
extern PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC                glgenDisableClientStateIndexedEXT;
extern PFNGLDISABLECLIENTSTATEIEXTPROC                      glgenDisableClientStateiEXT;
extern PFNGLDISABLEINDEXEDEXTPROC                           glgenDisableIndexedEXT;
extern PFNGLDISABLEVERTEXARRAYATTRIBPROC                    glgenDisableVertexArrayAttrib;
extern PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC                 glgenDisableVertexArrayAttribEXT;
extern PFNGLDISABLEVERTEXARRAYEXTPROC                       glgenDisableVertexArrayEXT;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC                    glgenDisableVertexAttribArray;
extern PFNGLDISABLEIPROC                                    glgenDisablei;
extern PFNGLDISPATCHCOMPUTEPROC                             glgenDispatchCompute;
extern PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC                 glgenDispatchComputeGroupSizeARB;
extern PFNGLDISPATCHCOMPUTEINDIRECTPROC                     glgenDispatchComputeIndirect;
extern PFNGLDRAWARRAYSPROC                                  glgenDrawArrays;
extern PFNGLDRAWARRAYSINDIRECTPROC                          glgenDrawArraysIndirect;
extern PFNGLDRAWARRAYSINSTANCEDPROC                         glgenDrawArraysInstanced;
extern PFNGLDRAWARRAYSINSTANCEDARBPROC                      glgenDrawArraysInstancedARB;
extern PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC             glgenDrawArraysInstancedBaseInstance;
extern PFNGLDRAWARRAYSINSTANCEDEXTPROC                      glgenDrawArraysInstancedEXT;
extern PFNGLDRAWBUFFERPROC                                  glgenDrawBuffer;
extern PFNGLDRAWBUFFERSPROC                                 glgenDrawBuffers;
extern PFNGLDRAWCOMMANDSADDRESSNVPROC                       glgenDrawCommandsAddressNV;
extern PFNGLDRAWCOMMANDSNVPROC                              glgenDrawCommandsNV;
extern PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC                 glgenDrawCommandsStatesAddressNV;
extern PFNGLDRAWCOMMANDSSTATESNVPROC                        glgenDrawCommandsStatesNV;
extern PFNGLDRAWELEMENTSPROC                                glgenDrawElements;
extern PFNGLDRAWELEMENTSBASEVERTEXPROC                      glgenDrawElementsBaseVertex;
extern PFNGLDRAWELEMENTSINDIRECTPROC                        glgenDrawElementsIndirect;
extern PFNGLDRAWELEMENTSINSTANCEDPROC                       glgenDrawElementsInstanced;
extern PFNGLDRAWELEMENTSINSTANCEDARBPROC                    glgenDrawElementsInstancedARB;
extern PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC           glgenDrawElementsInstancedBaseInstance;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC             glgenDrawElementsInstancedBaseVertex;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glgenDrawElementsInstancedBaseVertexBaseInstance;
extern PFNGLDRAWELEMENTSINSTANCEDEXTPROC                    glgenDrawElementsInstancedEXT;
extern PFNGLDRAWMESHTASKSINDIRECTNVPROC                     glgenDrawMeshTasksIndirectNV;
extern PFNGLDRAWMESHTASKSNVPROC                             glgenDrawMeshTasksNV;
extern PFNGLDRAWRANGEELEMENTSPROC                           glgenDrawRangeElements;
extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC                 glgenDrawRangeElementsBaseVertex;
extern PFNGLDRAWTRANSFORMFEEDBACKPROC                       glgenDrawTransformFeedback;
extern PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC              glgenDrawTransformFeedbackInstanced;
extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC                 glgenDrawTransformFeedbackStream;
extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC        glgenDrawTransformFeedbackStreamInstanced;
extern PFNGLDRAWVKIMAGENVPROC                               glgenDrawVkImageNV;
extern PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC                 glgenEGLImageTargetTexStorageEXT;
extern PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC             glgenEGLImageTargetTextureStorageEXT;
extern PFNGLEDGEFLAGFORMATNVPROC                            glgenEdgeFlagFormatNV;
extern PFNGLENABLEPROC                                      glgenEnable;
extern PFNGLENABLECLIENTSTATEINDEXEDEXTPROC                 glgenEnableClientStateIndexedEXT;
extern PFNGLENABLECLIENTSTATEIEXTPROC                       glgenEnableClientStateiEXT;
extern PFNGLENABLEINDEXEDEXTPROC                            glgenEnableIndexedEXT;
extern PFNGLENABLEVERTEXARRAYATTRIBPROC                     glgenEnableVertexArrayAttrib;
extern PFNGLENABLEVERTEXARRAYATTRIBEXTPROC                  glgenEnableVertexArrayAttribEXT;
extern PFNGLENABLEVERTEXARRAYEXTPROC                        glgenEnableVertexArrayEXT;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC                     glgenEnableVertexAttribArray;
extern PFNGLENABLEIPROC                                     glgenEnablei;
extern PFNGLENDCONDITIONALRENDERPROC                        glgenEndConditionalRender;
extern PFNGLENDCONDITIONALRENDERNVPROC                      glgenEndConditionalRenderNV;
extern PFNGLENDPERFMONITORAMDPROC                           glgenEndPerfMonitorAMD;
extern PFNGLENDPERFQUERYINTELPROC                           glgenEndPerfQueryINTEL;
extern PFNGLENDQUERYPROC                                    glgenEndQuery;
extern PFNGLENDQUERYINDEXEDPROC                             glgenEndQueryIndexed;
extern PFNGLENDTRANSFORMFEEDBACKPROC                        glgenEndTransformFeedback;
extern PFNGLEVALUATEDEPTHVALUESARBPROC                      glgenEvaluateDepthValuesARB;
extern PFNGLFENCESYNCPROC                                   glgenFenceSync;
extern PFNGLFINISHPROC                                      glgenFinish;
extern PFNGLFLUSHPROC                                       glgenFlush;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC                      glgenFlushMappedBufferRange;
extern PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC                 glgenFlushMappedNamedBufferRange;
extern PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC              glgenFlushMappedNamedBufferRangeEXT;
extern PFNGLFOGCOORDFORMATNVPROC                            glgenFogCoordFormatNV;
extern PFNGLFRAGMENTCOVERAGECOLORNVPROC                     glgenFragmentCoverageColorNV;
extern PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC                    glgenFramebufferDrawBufferEXT;
extern PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC                   glgenFramebufferDrawBuffersEXT;
extern PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC                  glgenFramebufferFetchBarrierEXT;
extern PFNGLFRAMEBUFFERPARAMETERIPROC                       glgenFramebufferParameteri;
extern PFNGLFRAMEBUFFERPARAMETERIMESAPROC                   glgenFramebufferParameteriMESA;
extern PFNGLFRAMEBUFFERREADBUFFEREXTPROC                    glgenFramebufferReadBufferEXT;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC                     glgenFramebufferRenderbuffer;
extern PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC             glgenFramebufferSampleLocationsfvARB;
extern PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC              glgenFramebufferSampleLocationsfvNV;
extern PFNGLFRAMEBUFFERTEXTUREPROC                          glgenFramebufferTexture;
extern PFNGLFRAMEBUFFERTEXTURE1DPROC                        glgenFramebufferTexture1D;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC                        glgenFramebufferTexture2D;
extern PFNGLFRAMEBUFFERTEXTURE3DPROC                        glgenFramebufferTexture3D;
extern PFNGLFRAMEBUFFERTEXTUREARBPROC                       glgenFramebufferTextureARB;
extern PFNGLFRAMEBUFFERTEXTUREFACEARBPROC                   glgenFramebufferTextureFaceARB;
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC                     glgenFramebufferTextureLayer;
extern PFNGLFRAMEBUFFERTEXTURELAYERARBPROC                  glgenFramebufferTextureLayerARB;
extern PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC              glgenFramebufferTextureMultiviewOVR;
extern PFNGLFRONTFACEPROC                                   glgenFrontFace;
extern PFNGLGENBUFFERSPROC                                  glgenGenBuffers;
extern PFNGLGENFRAMEBUFFERSPROC                             glgenGenFramebuffers;
extern PFNGLGENPATHSNVPROC                                  glgenGenPathsNV;
extern PFNGLGENPERFMONITORSAMDPROC                          glgenGenPerfMonitorsAMD;
extern PFNGLGENPROGRAMPIPELINESPROC                         glgenGenProgramPipelines;
extern PFNGLGENQUERIESPROC                                  glgenGenQueries;
extern PFNGLGENRENDERBUFFERSPROC                            glgenGenRenderbuffers;
extern PFNGLGENSAMPLERSPROC                                 glgenGenSamplers;
extern PFNGLGENTEXTURESPROC                                 glgenGenTextures;
extern PFNGLGENTRANSFORMFEEDBACKSPROC                       glgenGenTransformFeedbacks;
extern PFNGLGENVERTEXARRAYSPROC                             glgenGenVertexArrays;
extern PFNGLGENERATEMIPMAPPROC                              glgenGenerateMipmap;
extern PFNGLGENERATEMULTITEXMIPMAPEXTPROC                   glgenGenerateMultiTexMipmapEXT;
extern PFNGLGENERATETEXTUREMIPMAPPROC                       glgenGenerateTextureMipmap;
extern PFNGLGENERATETEXTUREMIPMAPEXTPROC                    glgenGenerateTextureMipmapEXT;
extern PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC              glgenGetActiveAtomicCounterBufferiv;
extern PFNGLGETACTIVEATTRIBPROC                             glgenGetActiveAttrib;
extern PFNGLGETACTIVESUBROUTINENAMEPROC                     glgenGetActiveSubroutineName;
extern PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC              glgenGetActiveSubroutineUniformName;
extern PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC                glgenGetActiveSubroutineUniformiv;
extern PFNGLGETACTIVEUNIFORMPROC                            glgenGetActiveUniform;
extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC                   glgenGetActiveUniformBlockName;
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC                     glgenGetActiveUniformBlockiv;
extern PFNGLGETACTIVEUNIFORMNAMEPROC                        glgenGetActiveUniformName;
extern PFNGLGETACTIVEUNIFORMSIVPROC                         glgenGetActiveUniformsiv;
extern PFNGLGETATTACHEDSHADERSPROC                          glgenGetAttachedShaders;
extern PFNGLGETATTRIBLOCATIONPROC                           glgenGetAttribLocation;
extern PFNGLGETBOOLEANINDEXEDVEXTPROC                       glgenGetBooleanIndexedvEXT;
extern PFNGLGETBOOLEANI_VPROC                               glgenGetBooleani_v;
extern PFNGLGETBOOLEANVPROC                                 glgenGetBooleanv;
extern PFNGLGETBUFFERPARAMETERI64VPROC                      glgenGetBufferParameteri64v;
extern PFNGLGETBUFFERPARAMETERIVPROC                        glgenGetBufferParameteriv;
extern PFNGLGETBUFFERPARAMETERUI64VNVPROC                   glgenGetBufferParameterui64vNV;
extern PFNGLGETBUFFERPOINTERVPROC                           glgenGetBufferPointerv;
extern PFNGLGETBUFFERSUBDATAPROC                            glgenGetBufferSubData;
extern PFNGLGETCOMMANDHEADERNVPROC                          glgenGetCommandHeaderNV;
extern PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC               glgenGetCompressedMultiTexImageEXT;
extern PFNGLGETCOMPRESSEDTEXIMAGEPROC                       glgenGetCompressedTexImage;
extern PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC                   glgenGetCompressedTextureImage;
extern PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC                glgenGetCompressedTextureImageEXT;
extern PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC                glgenGetCompressedTextureSubImage;
extern PFNGLGETCOVERAGEMODULATIONTABLENVPROC                glgenGetCoverageModulationTableNV;
extern PFNGLGETDEBUGMESSAGELOGPROC                          glgenGetDebugMessageLog;
extern PFNGLGETDEBUGMESSAGELOGARBPROC                       glgenGetDebugMessageLogARB;
extern PFNGLGETDOUBLEINDEXEDVEXTPROC                        glgenGetDoubleIndexedvEXT;
extern PFNGLGETDOUBLEI_VPROC                                glgenGetDoublei_v;
extern PFNGLGETDOUBLEI_VEXTPROC                             glgenGetDoublei_vEXT;
extern PFNGLGETDOUBLEVPROC                                  glgenGetDoublev;
extern PFNGLGETERRORPROC                                    glgenGetError;
extern PFNGLGETFIRSTPERFQUERYIDINTELPROC                    glgenGetFirstPerfQueryIdINTEL;
extern PFNGLGETFLOATINDEXEDVEXTPROC                         glgenGetFloatIndexedvEXT;
extern PFNGLGETFLOATI_VPROC                                 glgenGetFloati_v;
extern PFNGLGETFLOATI_VEXTPROC                              glgenGetFloati_vEXT;
extern PFNGLGETFLOATVPROC                                   glgenGetFloatv;
extern PFNGLGETFRAGDATAINDEXPROC                            glgenGetFragDataIndex;
extern PFNGLGETFRAGDATALOCATIONPROC                         glgenGetFragDataLocation;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC         glgenGetFramebufferAttachmentParameteriv;
extern PFNGLGETFRAMEBUFFERPARAMETERIVPROC                   glgenGetFramebufferParameteriv;
extern PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC                glgenGetFramebufferParameterivEXT;
extern PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC               glgenGetFramebufferParameterivMESA;
extern PFNGLGETGRAPHICSRESETSTATUSPROC                      glgenGetGraphicsResetStatus;
extern PFNGLGETGRAPHICSRESETSTATUSARBPROC                   glgenGetGraphicsResetStatusARB;
extern PFNGLGETIMAGEHANDLEARBPROC                           glgenGetImageHandleARB;
extern PFNGLGETIMAGEHANDLENVPROC                            glgenGetImageHandleNV;
extern PFNGLGETINTEGER64I_VPROC                             glgenGetInteger64i_v;
extern PFNGLGETINTEGER64VPROC                               glgenGetInteger64v;
extern PFNGLGETINTEGERINDEXEDVEXTPROC                       glgenGetIntegerIndexedvEXT;
extern PFNGLGETINTEGERI_VPROC                               glgenGetIntegeri_v;
extern PFNGLGETINTEGERUI64I_VNVPROC                         glgenGetIntegerui64i_vNV;
extern PFNGLGETINTEGERUI64VNVPROC                           glgenGetIntegerui64vNV;
extern PFNGLGETINTEGERVPROC                                 glgenGetIntegerv;
extern PFNGLGETINTERNALFORMATSAMPLEIVNVPROC                 glgenGetInternalformatSampleivNV;
extern PFNGLGETINTERNALFORMATI64VPROC                       glgenGetInternalformati64v;
extern PFNGLGETINTERNALFORMATIVPROC                         glgenGetInternalformativ;
extern PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC       glgenGetMemoryObjectDetachedResourcesuivNV;
extern PFNGLGETMULTITEXENVFVEXTPROC                         glgenGetMultiTexEnvfvEXT;
extern PFNGLGETMULTITEXENVIVEXTPROC                         glgenGetMultiTexEnvivEXT;
extern PFNGLGETMULTITEXGENDVEXTPROC                         glgenGetMultiTexGendvEXT;
extern PFNGLGETMULTITEXGENFVEXTPROC                         glgenGetMultiTexGenfvEXT;
extern PFNGLGETMULTITEXGENIVEXTPROC                         glgenGetMultiTexGenivEXT;
extern PFNGLGETMULTITEXIMAGEEXTPROC                         glgenGetMultiTexImageEXT;
extern PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC              glgenGetMultiTexLevelParameterfvEXT;
extern PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC              glgenGetMultiTexLevelParameterivEXT;
extern PFNGLGETMULTITEXPARAMETERIIVEXTPROC                  glgenGetMultiTexParameterIivEXT;
extern PFNGLGETMULTITEXPARAMETERIUIVEXTPROC                 glgenGetMultiTexParameterIuivEXT;
extern PFNGLGETMULTITEXPARAMETERFVEXTPROC                   glgenGetMultiTexParameterfvEXT;
extern PFNGLGETMULTITEXPARAMETERIVEXTPROC                   glgenGetMultiTexParameterivEXT;
extern PFNGLGETMULTISAMPLEFVPROC                            glgenGetMultisamplefv;
extern PFNGLGETNAMEDBUFFERPARAMETERI64VPROC                 glgenGetNamedBufferParameteri64v;
extern PFNGLGETNAMEDBUFFERPARAMETERIVPROC                   glgenGetNamedBufferParameteriv;
extern PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC                glgenGetNamedBufferParameterivEXT;
extern PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC              glgenGetNamedBufferParameterui64vNV;
extern PFNGLGETNAMEDBUFFERPOINTERVPROC                      glgenGetNamedBufferPointerv;
extern PFNGLGETNAMEDBUFFERPOINTERVEXTPROC                   glgenGetNamedBufferPointervEXT;
extern PFNGLGETNAMEDBUFFERSUBDATAPROC                       glgenGetNamedBufferSubData;
extern PFNGLGETNAMEDBUFFERSUBDATAEXTPROC                    glgenGetNamedBufferSubDataEXT;
extern PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC    glgenGetNamedFramebufferAttachmentParameteriv;
extern PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glgenGetNamedFramebufferAttachmentParameterivEXT;
extern PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC              glgenGetNamedFramebufferParameteriv;
extern PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC           glgenGetNamedFramebufferParameterivEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC         glgenGetNamedProgramLocalParameterIivEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC        glgenGetNamedProgramLocalParameterIuivEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC          glgenGetNamedProgramLocalParameterdvEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC          glgenGetNamedProgramLocalParameterfvEXT;
extern PFNGLGETNAMEDPROGRAMSTRINGEXTPROC                    glgenGetNamedProgramStringEXT;
extern PFNGLGETNAMEDPROGRAMIVEXTPROC                        glgenGetNamedProgramivEXT;
extern PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC             glgenGetNamedRenderbufferParameteriv;
extern PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC          glgenGetNamedRenderbufferParameterivEXT;
extern PFNGLGETNAMEDSTRINGARBPROC                           glgenGetNamedStringARB;
extern PFNGLGETNAMEDSTRINGIVARBPROC                         glgenGetNamedStringivARB;
extern PFNGLGETNEXTPERFQUERYIDINTELPROC                     glgenGetNextPerfQueryIdINTEL;
extern PFNGLGETOBJECTLABELPROC                              glgenGetObjectLabel;
extern PFNGLGETOBJECTLABELEXTPROC                           glgenGetObjectLabelEXT;
extern PFNGLGETOBJECTPTRLABELPROC                           glgenGetObjectPtrLabel;
extern PFNGLGETPATHCOMMANDSNVPROC                           glgenGetPathCommandsNV;
extern PFNGLGETPATHCOORDSNVPROC                             glgenGetPathCoordsNV;
extern PFNGLGETPATHDASHARRAYNVPROC                          glgenGetPathDashArrayNV;
extern PFNGLGETPATHLENGTHNVPROC                             glgenGetPathLengthNV;
extern PFNGLGETPATHMETRICRANGENVPROC                        glgenGetPathMetricRangeNV;
extern PFNGLGETPATHMETRICSNVPROC                            glgenGetPathMetricsNV;
extern PFNGLGETPATHPARAMETERFVNVPROC                        glgenGetPathParameterfvNV;
extern PFNGLGETPATHPARAMETERIVNVPROC                        glgenGetPathParameterivNV;
extern PFNGLGETPATHSPACINGNVPROC                            glgenGetPathSpacingNV;
extern PFNGLGETPERFCOUNTERINFOINTELPROC                     glgenGetPerfCounterInfoINTEL;
extern PFNGLGETPERFMONITORCOUNTERDATAAMDPROC                glgenGetPerfMonitorCounterDataAMD;
extern PFNGLGETPERFMONITORCOUNTERINFOAMDPROC                glgenGetPerfMonitorCounterInfoAMD;
extern PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC              glgenGetPerfMonitorCounterStringAMD;
extern PFNGLGETPERFMONITORCOUNTERSAMDPROC                   glgenGetPerfMonitorCountersAMD;
extern PFNGLGETPERFMONITORGROUPSTRINGAMDPROC                glgenGetPerfMonitorGroupStringAMD;
extern PFNGLGETPERFMONITORGROUPSAMDPROC                     glgenGetPerfMonitorGroupsAMD;
extern PFNGLGETPERFQUERYDATAINTELPROC                       glgenGetPerfQueryDataINTEL;
extern PFNGLGETPERFQUERYIDBYNAMEINTELPROC                   glgenGetPerfQueryIdByNameINTEL;
extern PFNGLGETPERFQUERYINFOINTELPROC                       glgenGetPerfQueryInfoINTEL;
extern PFNGLGETPOINTERINDEXEDVEXTPROC                       glgenGetPointerIndexedvEXT;
extern PFNGLGETPOINTERI_VEXTPROC                            glgenGetPointeri_vEXT;
extern PFNGLGETPOINTERVPROC                                 glgenGetPointerv;
extern PFNGLGETPROGRAMBINARYPROC                            glgenGetProgramBinary;
extern PFNGLGETPROGRAMINFOLOGPROC                           glgenGetProgramInfoLog;
extern PFNGLGETPROGRAMINTERFACEIVPROC                       glgenGetProgramInterfaceiv;
extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC                   glgenGetProgramPipelineInfoLog;
extern PFNGLGETPROGRAMPIPELINEIVPROC                        glgenGetProgramPipelineiv;
extern PFNGLGETPROGRAMRESOURCEINDEXPROC                     glgenGetProgramResourceIndex;
extern PFNGLGETPROGRAMRESOURCELOCATIONPROC                  glgenGetProgramResourceLocation;
extern PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC             glgenGetProgramResourceLocationIndex;
extern PFNGLGETPROGRAMRESOURCENAMEPROC                      glgenGetProgramResourceName;
extern PFNGLGETPROGRAMRESOURCEFVNVPROC                      glgenGetProgramResourcefvNV;
extern PFNGLGETPROGRAMRESOURCEIVPROC                        glgenGetProgramResourceiv;
extern PFNGLGETPROGRAMSTAGEIVPROC                           glgenGetProgramStageiv;
extern PFNGLGETPROGRAMIVPROC                                glgenGetProgramiv;
extern PFNGLGETQUERYBUFFEROBJECTI64VPROC                    glgenGetQueryBufferObjecti64v;
extern PFNGLGETQUERYBUFFEROBJECTIVPROC                      glgenGetQueryBufferObjectiv;
extern PFNGLGETQUERYBUFFEROBJECTUI64VPROC                   glgenGetQueryBufferObjectui64v;
extern PFNGLGETQUERYBUFFEROBJECTUIVPROC                     glgenGetQueryBufferObjectuiv;
extern PFNGLGETQUERYINDEXEDIVPROC                           glgenGetQueryIndexediv;
extern PFNGLGETQUERYOBJECTI64VPROC                          glgenGetQueryObjecti64v;
extern PFNGLGETQUERYOBJECTIVPROC                            glgenGetQueryObjectiv;
extern PFNGLGETQUERYOBJECTUI64VPROC                         glgenGetQueryObjectui64v;
extern PFNGLGETQUERYOBJECTUIVPROC                           glgenGetQueryObjectuiv;
extern PFNGLGETQUERYIVPROC                                  glgenGetQueryiv;
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC                  glgenGetRenderbufferParameteriv;
extern PFNGLGETSAMPLERPARAMETERIIVPROC                      glgenGetSamplerParameterIiv;
extern PFNGLGETSAMPLERPARAMETERIUIVPROC                     glgenGetSamplerParameterIuiv;
extern PFNGLGETSAMPLERPARAMETERFVPROC                       glgenGetSamplerParameterfv;
extern PFNGLGETSAMPLERPARAMETERIVPROC                       glgenGetSamplerParameteriv;
extern PFNGLGETSHADERINFOLOGPROC                            glgenGetShaderInfoLog;
extern PFNGLGETSHADERPRECISIONFORMATPROC                    glgenGetShaderPrecisionFormat;
extern PFNGLGETSHADERSOURCEPROC                             glgenGetShaderSource;
extern PFNGLGETSHADERIVPROC                                 glgenGetShaderiv;
extern PFNGLGETSHADINGRATEIMAGEPALETTENVPROC                glgenGetShadingRateImagePaletteNV;
extern PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC            glgenGetShadingRateSampleLocationivNV;
extern PFNGLGETSTAGEINDEXNVPROC                             glgenGetStageIndexNV;
extern PFNGLGETSTRINGPROC                                   glgenGetString;
extern PFNGLGETSTRINGIPROC                                  glgenGetStringi;
extern PFNGLGETSUBROUTINEINDEXPROC                          glgenGetSubroutineIndex;
extern PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC                glgenGetSubroutineUniformLocation;
extern PFNGLGETSYNCIVPROC                                   glgenGetSynciv;
extern PFNGLGETTEXIMAGEPROC                                 glgenGetTexImage;
extern PFNGLGETTEXLEVELPARAMETERFVPROC                      glgenGetTexLevelParameterfv;
extern PFNGLGETTEXLEVELPARAMETERIVPROC                      glgenGetTexLevelParameteriv;
extern PFNGLGETTEXPARAMETERIIVPROC                          glgenGetTexParameterIiv;
extern PFNGLGETTEXPARAMETERIUIVPROC                         glgenGetTexParameterIuiv;
extern PFNGLGETTEXPARAMETERFVPROC                           glgenGetTexParameterfv;
extern PFNGLGETTEXPARAMETERIVPROC                           glgenGetTexParameteriv;
extern PFNGLGETTEXTUREHANDLEARBPROC                         glgenGetTextureHandleARB;
extern PFNGLGETTEXTUREHANDLENVPROC                          glgenGetTextureHandleNV;
extern PFNGLGETTEXTUREIMAGEPROC                             glgenGetTextureImage;
extern PFNGLGETTEXTUREIMAGEEXTPROC                          glgenGetTextureImageEXT;
extern PFNGLGETTEXTURELEVELPARAMETERFVPROC                  glgenGetTextureLevelParameterfv;
extern PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC               glgenGetTextureLevelParameterfvEXT;
extern PFNGLGETTEXTURELEVELPARAMETERIVPROC                  glgenGetTextureLevelParameteriv;
extern PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC               glgenGetTextureLevelParameterivEXT;
extern PFNGLGETTEXTUREPARAMETERIIVPROC                      glgenGetTextureParameterIiv;
extern PFNGLGETTEXTUREPARAMETERIIVEXTPROC                   glgenGetTextureParameterIivEXT;
extern PFNGLGETTEXTUREPARAMETERIUIVPROC                     glgenGetTextureParameterIuiv;
extern PFNGLGETTEXTUREPARAMETERIUIVEXTPROC                  glgenGetTextureParameterIuivEXT;
extern PFNGLGETTEXTUREPARAMETERFVPROC                       glgenGetTextureParameterfv;
extern PFNGLGETTEXTUREPARAMETERFVEXTPROC                    glgenGetTextureParameterfvEXT;
extern PFNGLGETTEXTUREPARAMETERIVPROC                       glgenGetTextureParameteriv;
extern PFNGLGETTEXTUREPARAMETERIVEXTPROC                    glgenGetTextureParameterivEXT;
extern PFNGLGETTEXTURESAMPLERHANDLEARBPROC                  glgenGetTextureSamplerHandleARB;
extern PFNGLGETTEXTURESAMPLERHANDLENVPROC                   glgenGetTextureSamplerHandleNV;
extern PFNGLGETTEXTURESUBIMAGEPROC                          glgenGetTextureSubImage;
extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC                 glgenGetTransformFeedbackVarying;
extern PFNGLGETTRANSFORMFEEDBACKI64_VPROC                   glgenGetTransformFeedbacki64_v;
extern PFNGLGETTRANSFORMFEEDBACKI_VPROC                     glgenGetTransformFeedbacki_v;
extern PFNGLGETTRANSFORMFEEDBACKIVPROC                      glgenGetTransformFeedbackiv;
extern PFNGLGETUNIFORMBLOCKINDEXPROC                        glgenGetUniformBlockIndex;
extern PFNGLGETUNIFORMINDICESPROC                           glgenGetUniformIndices;
extern PFNGLGETUNIFORMLOCATIONPROC                          glgenGetUniformLocation;
extern PFNGLGETUNIFORMSUBROUTINEUIVPROC                     glgenGetUniformSubroutineuiv;
extern PFNGLGETUNIFORMDVPROC                                glgenGetUniformdv;
extern PFNGLGETUNIFORMFVPROC                                glgenGetUniformfv;
extern PFNGLGETUNIFORMI64VARBPROC                           glgenGetUniformi64vARB;
extern PFNGLGETUNIFORMI64VNVPROC                            glgenGetUniformi64vNV;
extern PFNGLGETUNIFORMIVPROC                                glgenGetUniformiv;
extern PFNGLGETUNIFORMUI64VARBPROC                          glgenGetUniformui64vARB;
extern PFNGLGETUNIFORMUI64VNVPROC                           glgenGetUniformui64vNV;
extern PFNGLGETUNIFORMUIVPROC                               glgenGetUniformuiv;
extern PFNGLGETVERTEXARRAYINDEXED64IVPROC                   glgenGetVertexArrayIndexed64iv;
extern PFNGLGETVERTEXARRAYINDEXEDIVPROC                     glgenGetVertexArrayIndexediv;
extern PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC                 glgenGetVertexArrayIntegeri_vEXT;
extern PFNGLGETVERTEXARRAYINTEGERVEXTPROC                   glgenGetVertexArrayIntegervEXT;
extern PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC                 glgenGetVertexArrayPointeri_vEXT;
extern PFNGLGETVERTEXARRAYPOINTERVEXTPROC                   glgenGetVertexArrayPointervEXT;
extern PFNGLGETVERTEXARRAYIVPROC                            glgenGetVertexArrayiv;
extern PFNGLGETVERTEXATTRIBIIVPROC                          glgenGetVertexAttribIiv;
extern PFNGLGETVERTEXATTRIBIUIVPROC                         glgenGetVertexAttribIuiv;
extern PFNGLGETVERTEXATTRIBLDVPROC                          glgenGetVertexAttribLdv;
extern PFNGLGETVERTEXATTRIBLI64VNVPROC                      glgenGetVertexAttribLi64vNV;
extern PFNGLGETVERTEXATTRIBLUI64VARBPROC                    glgenGetVertexAttribLui64vARB;
extern PFNGLGETVERTEXATTRIBLUI64VNVPROC                     glgenGetVertexAttribLui64vNV;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC                     glgenGetVertexAttribPointerv;
extern PFNGLGETVERTEXATTRIBDVPROC                           glgenGetVertexAttribdv;
extern PFNGLGETVERTEXATTRIBFVPROC                           glgenGetVertexAttribfv;
extern PFNGLGETVERTEXATTRIBIVPROC                           glgenGetVertexAttribiv;
extern PFNGLGETVKPROCADDRNVPROC                             glgenGetVkProcAddrNV;
extern PFNGLGETNCOMPRESSEDTEXIMAGEPROC                      glgenGetnCompressedTexImage;
extern PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC                   glgenGetnCompressedTexImageARB;
extern PFNGLGETNTEXIMAGEPROC                                glgenGetnTexImage;
extern PFNGLGETNTEXIMAGEARBPROC                             glgenGetnTexImageARB;
extern PFNGLGETNUNIFORMDVPROC                               glgenGetnUniformdv;
extern PFNGLGETNUNIFORMDVARBPROC                            glgenGetnUniformdvARB;
extern PFNGLGETNUNIFORMFVPROC                               glgenGetnUniformfv;
extern PFNGLGETNUNIFORMFVARBPROC                            glgenGetnUniformfvARB;
extern PFNGLGETNUNIFORMI64VARBPROC                          glgenGetnUniformi64vARB;
extern PFNGLGETNUNIFORMIVPROC                               glgenGetnUniformiv;
extern PFNGLGETNUNIFORMIVARBPROC                            glgenGetnUniformivARB;
extern PFNGLGETNUNIFORMUI64VARBPROC                         glgenGetnUniformui64vARB;
extern PFNGLGETNUNIFORMUIVPROC                              glgenGetnUniformuiv;
extern PFNGLGETNUNIFORMUIVARBPROC                           glgenGetnUniformuivARB;
extern PFNGLHINTPROC                                        glgenHint;
extern PFNGLINDEXFORMATNVPROC                               glgenIndexFormatNV;
extern PFNGLINSERTEVENTMARKEREXTPROC                        glgenInsertEventMarkerEXT;
extern PFNGLINTERPOLATEPATHSNVPROC                          glgenInterpolatePathsNV;
extern PFNGLINVALIDATEBUFFERDATAPROC                        glgenInvalidateBufferData;
extern PFNGLINVALIDATEBUFFERSUBDATAPROC                     glgenInvalidateBufferSubData;
extern PFNGLINVALIDATEFRAMEBUFFERPROC                       glgenInvalidateFramebuffer;
extern PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC              glgenInvalidateNamedFramebufferData;
extern PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC           glgenInvalidateNamedFramebufferSubData;
extern PFNGLINVALIDATESUBFRAMEBUFFERPROC                    glgenInvalidateSubFramebuffer;
extern PFNGLINVALIDATETEXIMAGEPROC                          glgenInvalidateTexImage;
extern PFNGLINVALIDATETEXSUBIMAGEPROC                       glgenInvalidateTexSubImage;
extern PFNGLISBUFFERPROC                                    glgenIsBuffer;
extern PFNGLISBUFFERRESIDENTNVPROC                          glgenIsBufferResidentNV;
extern PFNGLISCOMMANDLISTNVPROC                             glgenIsCommandListNV;
extern PFNGLISENABLEDPROC                                   glgenIsEnabled;
extern PFNGLISENABLEDINDEXEDEXTPROC                         glgenIsEnabledIndexedEXT;
extern PFNGLISENABLEDIPROC                                  glgenIsEnabledi;
extern PFNGLISFRAMEBUFFERPROC                               glgenIsFramebuffer;
extern PFNGLISIMAGEHANDLERESIDENTARBPROC                    glgenIsImageHandleResidentARB;
extern PFNGLISIMAGEHANDLERESIDENTNVPROC                     glgenIsImageHandleResidentNV;
extern PFNGLISNAMEDBUFFERRESIDENTNVPROC                     glgenIsNamedBufferResidentNV;
extern PFNGLISNAMEDSTRINGARBPROC                            glgenIsNamedStringARB;
extern PFNGLISPATHNVPROC                                    glgenIsPathNV;
extern PFNGLISPOINTINFILLPATHNVPROC                         glgenIsPointInFillPathNV;
extern PFNGLISPOINTINSTROKEPATHNVPROC                       glgenIsPointInStrokePathNV;
extern PFNGLISPROGRAMPROC                                   glgenIsProgram;
extern PFNGLISPROGRAMPIPELINEPROC                           glgenIsProgramPipeline;
extern PFNGLISQUERYPROC                                     glgenIsQuery;
extern PFNGLISRENDERBUFFERPROC                              glgenIsRenderbuffer;
extern PFNGLISSAMPLERPROC                                   glgenIsSampler;
extern PFNGLISSHADERPROC                                    glgenIsShader;
extern PFNGLISSTATENVPROC                                   glgenIsStateNV;
extern PFNGLISSYNCPROC                                      glgenIsSync;
extern PFNGLISTEXTUREPROC                                   glgenIsTexture;
extern PFNGLISTEXTUREHANDLERESIDENTARBPROC                  glgenIsTextureHandleResidentARB;
extern PFNGLISTEXTUREHANDLERESIDENTNVPROC                   glgenIsTextureHandleResidentNV;
extern PFNGLISTRANSFORMFEEDBACKPROC                         glgenIsTransformFeedback;
extern PFNGLISVERTEXARRAYPROC                               glgenIsVertexArray;
extern PFNGLLABELOBJECTEXTPROC                              glgenLabelObjectEXT;
extern PFNGLLINEWIDTHPROC                                   glgenLineWidth;
extern PFNGLLINKPROGRAMPROC                                 glgenLinkProgram;
extern PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC              glgenListDrawCommandsStatesClientNV;
extern PFNGLLOGICOPPROC                                     glgenLogicOp;
extern PFNGLMAKEBUFFERNONRESIDENTNVPROC                     glgenMakeBufferNonResidentNV;
extern PFNGLMAKEBUFFERRESIDENTNVPROC                        glgenMakeBufferResidentNV;
extern PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC               glgenMakeImageHandleNonResidentARB;
extern PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC                glgenMakeImageHandleNonResidentNV;
extern PFNGLMAKEIMAGEHANDLERESIDENTARBPROC                  glgenMakeImageHandleResidentARB;
extern PFNGLMAKEIMAGEHANDLERESIDENTNVPROC                   glgenMakeImageHandleResidentNV;
extern PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC                glgenMakeNamedBufferNonResidentNV;
extern PFNGLMAKENAMEDBUFFERRESIDENTNVPROC                   glgenMakeNamedBufferResidentNV;
extern PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC             glgenMakeTextureHandleNonResidentARB;
extern PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC              glgenMakeTextureHandleNonResidentNV;
extern PFNGLMAKETEXTUREHANDLERESIDENTARBPROC                glgenMakeTextureHandleResidentARB;
extern PFNGLMAKETEXTUREHANDLERESIDENTNVPROC                 glgenMakeTextureHandleResidentNV;
extern PFNGLMAPBUFFERPROC                                   glgenMapBuffer;
extern PFNGLMAPBUFFERRANGEPROC                              glgenMapBufferRange;
extern PFNGLMAPNAMEDBUFFERPROC                              glgenMapNamedBuffer;
extern PFNGLMAPNAMEDBUFFEREXTPROC                           glgenMapNamedBufferEXT;
extern PFNGLMAPNAMEDBUFFERRANGEPROC                         glgenMapNamedBufferRange;
extern PFNGLMAPNAMEDBUFFERRANGEEXTPROC                      glgenMapNamedBufferRangeEXT;
extern PFNGLMATRIXFRUSTUMEXTPROC                            glgenMatrixFrustumEXT;
extern PFNGLMATRIXLOAD3X2FNVPROC                            glgenMatrixLoad3x2fNV;
extern PFNGLMATRIXLOAD3X3FNVPROC                            glgenMatrixLoad3x3fNV;
extern PFNGLMATRIXLOADIDENTITYEXTPROC                       glgenMatrixLoadIdentityEXT;
extern PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC                   glgenMatrixLoadTranspose3x3fNV;
extern PFNGLMATRIXLOADTRANSPOSEDEXTPROC                     glgenMatrixLoadTransposedEXT;
extern PFNGLMATRIXLOADTRANSPOSEFEXTPROC                     glgenMatrixLoadTransposefEXT;
extern PFNGLMATRIXLOADDEXTPROC                              glgenMatrixLoaddEXT;
extern PFNGLMATRIXLOADFEXTPROC                              glgenMatrixLoadfEXT;
extern PFNGLMATRIXMULT3X2FNVPROC                            glgenMatrixMult3x2fNV;
extern PFNGLMATRIXMULT3X3FNVPROC                            glgenMatrixMult3x3fNV;
extern PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC                   glgenMatrixMultTranspose3x3fNV;
extern PFNGLMATRIXMULTTRANSPOSEDEXTPROC                     glgenMatrixMultTransposedEXT;
extern PFNGLMATRIXMULTTRANSPOSEFEXTPROC                     glgenMatrixMultTransposefEXT;
extern PFNGLMATRIXMULTDEXTPROC                              glgenMatrixMultdEXT;
extern PFNGLMATRIXMULTFEXTPROC                              glgenMatrixMultfEXT;
extern PFNGLMATRIXORTHOEXTPROC                              glgenMatrixOrthoEXT;
extern PFNGLMATRIXPOPEXTPROC                                glgenMatrixPopEXT;
extern PFNGLMATRIXPUSHEXTPROC                               glgenMatrixPushEXT;
extern PFNGLMATRIXROTATEDEXTPROC                            glgenMatrixRotatedEXT;
extern PFNGLMATRIXROTATEFEXTPROC                            glgenMatrixRotatefEXT;
extern PFNGLMATRIXSCALEDEXTPROC                             glgenMatrixScaledEXT;
extern PFNGLMATRIXSCALEFEXTPROC                             glgenMatrixScalefEXT;
extern PFNGLMATRIXTRANSLATEDEXTPROC                         glgenMatrixTranslatedEXT;
extern PFNGLMATRIXTRANSLATEFEXTPROC                         glgenMatrixTranslatefEXT;
extern PFNGLMAXSHADERCOMPILERTHREADSARBPROC                 glgenMaxShaderCompilerThreadsARB;
extern PFNGLMAXSHADERCOMPILERTHREADSKHRPROC                 glgenMaxShaderCompilerThreadsKHR;
extern PFNGLMEMORYBARRIERPROC                               glgenMemoryBarrier;
extern PFNGLMEMORYBARRIERBYREGIONPROC                       glgenMemoryBarrierByRegion;
extern PFNGLMINSAMPLESHADINGPROC                            glgenMinSampleShading;
extern PFNGLMINSAMPLESHADINGARBPROC                         glgenMinSampleShadingARB;
extern PFNGLMULTIDRAWARRAYSPROC                             glgenMultiDrawArrays;
extern PFNGLMULTIDRAWARRAYSINDIRECTPROC                     glgenMultiDrawArraysIndirect;
extern PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC      glgenMultiDrawArraysIndirectBindlessCountNV;
extern PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC           glgenMultiDrawArraysIndirectBindlessNV;
extern PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC                glgenMultiDrawArraysIndirectCount;
extern PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC             glgenMultiDrawArraysIndirectCountARB;
extern PFNGLMULTIDRAWELEMENTSPROC                           glgenMultiDrawElements;
extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC                 glgenMultiDrawElementsBaseVertex;
extern PFNGLMULTIDRAWELEMENTSINDIRECTPROC                   glgenMultiDrawElementsIndirect;
extern PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC    glgenMultiDrawElementsIndirectBindlessCountNV;
extern PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC         glgenMultiDrawElementsIndirectBindlessNV;
extern PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC              glgenMultiDrawElementsIndirectCount;
extern PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC           glgenMultiDrawElementsIndirectCountARB;
extern PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC           glgenMultiDrawMeshTasksIndirectCountNV;
extern PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC                glgenMultiDrawMeshTasksIndirectNV;
extern PFNGLMULTITEXBUFFEREXTPROC                           glgenMultiTexBufferEXT;
extern PFNGLMULTITEXCOORDPOINTEREXTPROC                     glgenMultiTexCoordPointerEXT;
extern PFNGLMULTITEXENVFEXTPROC                             glgenMultiTexEnvfEXT;
extern PFNGLMULTITEXENVFVEXTPROC                            glgenMultiTexEnvfvEXT;
extern PFNGLMULTITEXENVIEXTPROC                             glgenMultiTexEnviEXT;
extern PFNGLMULTITEXENVIVEXTPROC                            glgenMultiTexEnvivEXT;
extern PFNGLMULTITEXGENDEXTPROC                             glgenMultiTexGendEXT;
extern PFNGLMULTITEXGENDVEXTPROC                            glgenMultiTexGendvEXT;
extern PFNGLMULTITEXGENFEXTPROC                             glgenMultiTexGenfEXT;
extern PFNGLMULTITEXGENFVEXTPROC                            glgenMultiTexGenfvEXT;
extern PFNGLMULTITEXGENIEXTPROC                             glgenMultiTexGeniEXT;
extern PFNGLMULTITEXGENIVEXTPROC                            glgenMultiTexGenivEXT;
extern PFNGLMULTITEXIMAGE1DEXTPROC                          glgenMultiTexImage1DEXT;
extern PFNGLMULTITEXIMAGE2DEXTPROC                          glgenMultiTexImage2DEXT;
extern PFNGLMULTITEXIMAGE3DEXTPROC                          glgenMultiTexImage3DEXT;
extern PFNGLMULTITEXPARAMETERIIVEXTPROC                     glgenMultiTexParameterIivEXT;
extern PFNGLMULTITEXPARAMETERIUIVEXTPROC                    glgenMultiTexParameterIuivEXT;
extern PFNGLMULTITEXPARAMETERFEXTPROC                       glgenMultiTexParameterfEXT;
extern PFNGLMULTITEXPARAMETERFVEXTPROC                      glgenMultiTexParameterfvEXT;
extern PFNGLMULTITEXPARAMETERIEXTPROC                       glgenMultiTexParameteriEXT;
extern PFNGLMULTITEXPARAMETERIVEXTPROC                      glgenMultiTexParameterivEXT;
extern PFNGLMULTITEXRENDERBUFFEREXTPROC                     glgenMultiTexRenderbufferEXT;
extern PFNGLMULTITEXSUBIMAGE1DEXTPROC                       glgenMultiTexSubImage1DEXT;
extern PFNGLMULTITEXSUBIMAGE2DEXTPROC                       glgenMultiTexSubImage2DEXT;
extern PFNGLMULTITEXSUBIMAGE3DEXTPROC                       glgenMultiTexSubImage3DEXT;
extern PFNGLNAMEDBUFFERATTACHMEMORYNVPROC                   glgenNamedBufferAttachMemoryNV;
extern PFNGLNAMEDBUFFERDATAPROC                             glgenNamedBufferData;
extern PFNGLNAMEDBUFFERDATAEXTPROC                          glgenNamedBufferDataEXT;
extern PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC                glgenNamedBufferPageCommitmentARB;
extern PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC                glgenNamedBufferPageCommitmentEXT;
extern PFNGLNAMEDBUFFERSTORAGEPROC                          glgenNamedBufferStorage;
extern PFNGLNAMEDBUFFERSTORAGEEXTPROC                       glgenNamedBufferStorageEXT;
extern PFNGLNAMEDBUFFERSUBDATAPROC                          glgenNamedBufferSubData;
extern PFNGLNAMEDBUFFERSUBDATAEXTPROC                       glgenNamedBufferSubDataEXT;
extern PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC                   glgenNamedCopyBufferSubDataEXT;
extern PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC                  glgenNamedFramebufferDrawBuffer;
extern PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC                 glgenNamedFramebufferDrawBuffers;
extern PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC                  glgenNamedFramebufferParameteri;
extern PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC               glgenNamedFramebufferParameteriEXT;
extern PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC                  glgenNamedFramebufferReadBuffer;
extern PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC                glgenNamedFramebufferRenderbuffer;
extern PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC             glgenNamedFramebufferRenderbufferEXT;
extern PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC        glgenNamedFramebufferSampleLocationsfvARB;
extern PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC         glgenNamedFramebufferSampleLocationsfvNV;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREPROC                     glgenNamedFramebufferTexture;
extern PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC                glgenNamedFramebufferTexture1DEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC                glgenNamedFramebufferTexture2DEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC                glgenNamedFramebufferTexture3DEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC                  glgenNamedFramebufferTextureEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC              glgenNamedFramebufferTextureFaceEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC                glgenNamedFramebufferTextureLayer;
extern PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC             glgenNamedFramebufferTextureLayerEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC             glgenNamedProgramLocalParameter4dEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC            glgenNamedProgramLocalParameter4dvEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC             glgenNamedProgramLocalParameter4fEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC            glgenNamedProgramLocalParameter4fvEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC            glgenNamedProgramLocalParameterI4iEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC           glgenNamedProgramLocalParameterI4ivEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC           glgenNamedProgramLocalParameterI4uiEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC          glgenNamedProgramLocalParameterI4uivEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC           glgenNamedProgramLocalParameters4fvEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC          glgenNamedProgramLocalParametersI4ivEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC         glgenNamedProgramLocalParametersI4uivEXT;
extern PFNGLNAMEDPROGRAMSTRINGEXTPROC                       glgenNamedProgramStringEXT;
extern PFNGLNAMEDRENDERBUFFERSTORAGEPROC                    glgenNamedRenderbufferStorage;
extern PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC                 glgenNamedRenderbufferStorageEXT;
extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC         glgenNamedRenderbufferStorageMultisample;
extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC glgenNamedRenderbufferStorageMultisampleAdvancedAMD;
extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC glgenNamedRenderbufferStorageMultisampleCoverageEXT;
extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC      glgenNamedRenderbufferStorageMultisampleEXT;
extern PFNGLNAMEDSTRINGARBPROC                              glgenNamedStringARB;
extern PFNGLNORMALFORMATNVPROC                              glgenNormalFormatNV;
extern PFNGLOBJECTLABELPROC                                 glgenObjectLabel;
extern PFNGLOBJECTPTRLABELPROC                              glgenObjectPtrLabel;
extern PFNGLPATCHPARAMETERFVPROC                            glgenPatchParameterfv;
extern PFNGLPATCHPARAMETERIPROC                             glgenPatchParameteri;
extern PFNGLPATHCOMMANDSNVPROC                              glgenPathCommandsNV;
extern PFNGLPATHCOORDSNVPROC                                glgenPathCoordsNV;
extern PFNGLPATHCOVERDEPTHFUNCNVPROC                        glgenPathCoverDepthFuncNV;
extern PFNGLPATHDASHARRAYNVPROC                             glgenPathDashArrayNV;
extern PFNGLPATHGLYPHINDEXARRAYNVPROC                       glgenPathGlyphIndexArrayNV;
extern PFNGLPATHGLYPHINDEXRANGENVPROC                       glgenPathGlyphIndexRangeNV;
extern PFNGLPATHGLYPHRANGENVPROC                            glgenPathGlyphRangeNV;
extern PFNGLPATHGLYPHSNVPROC                                glgenPathGlyphsNV;
extern PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC                 glgenPathMemoryGlyphIndexArrayNV;
extern PFNGLPATHPARAMETERFNVPROC                            glgenPathParameterfNV;
extern PFNGLPATHPARAMETERFVNVPROC                           glgenPathParameterfvNV;
extern PFNGLPATHPARAMETERINVPROC                            glgenPathParameteriNV;
extern PFNGLPATHPARAMETERIVNVPROC                           glgenPathParameterivNV;
extern PFNGLPATHSTENCILDEPTHOFFSETNVPROC                    glgenPathStencilDepthOffsetNV;
extern PFNGLPATHSTENCILFUNCNVPROC                           glgenPathStencilFuncNV;
extern PFNGLPATHSTRINGNVPROC                                glgenPathStringNV;
extern PFNGLPATHSUBCOMMANDSNVPROC                           glgenPathSubCommandsNV;
extern PFNGLPATHSUBCOORDSNVPROC                             glgenPathSubCoordsNV;
extern PFNGLPAUSETRANSFORMFEEDBACKPROC                      glgenPauseTransformFeedback;
extern PFNGLPIXELSTOREFPROC                                 glgenPixelStoref;
extern PFNGLPIXELSTOREIPROC                                 glgenPixelStorei;
extern PFNGLPOINTALONGPATHNVPROC                            glgenPointAlongPathNV;
extern PFNGLPOINTPARAMETERFPROC                             glgenPointParameterf;
extern PFNGLPOINTPARAMETERFVPROC                            glgenPointParameterfv;
extern PFNGLPOINTPARAMETERIPROC                             glgenPointParameteri;
extern PFNGLPOINTPARAMETERIVPROC                            glgenPointParameteriv;
extern PFNGLPOINTSIZEPROC                                   glgenPointSize;
extern PFNGLPOLYGONMODEPROC                                 glgenPolygonMode;
extern PFNGLPOLYGONOFFSETPROC                               glgenPolygonOffset;
extern PFNGLPOLYGONOFFSETCLAMPPROC                          glgenPolygonOffsetClamp;
extern PFNGLPOLYGONOFFSETCLAMPEXTPROC                       glgenPolygonOffsetClampEXT;
extern PFNGLPOPDEBUGGROUPPROC                               glgenPopDebugGroup;
extern PFNGLPOPGROUPMARKEREXTPROC                           glgenPopGroupMarkerEXT;
extern PFNGLPRIMITIVEBOUNDINGBOXARBPROC                     glgenPrimitiveBoundingBoxARB;
extern PFNGLPRIMITIVERESTARTINDEXPROC                       glgenPrimitiveRestartIndex;
extern PFNGLPROGRAMBINARYPROC                               glgenProgramBinary;
extern PFNGLPROGRAMPARAMETERIPROC                           glgenProgramParameteri;
extern PFNGLPROGRAMPARAMETERIARBPROC                        glgenProgramParameteriARB;
extern PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC               glgenProgramPathFragmentInputGenNV;
extern PFNGLPROGRAMUNIFORM1DPROC                            glgenProgramUniform1d;
extern PFNGLPROGRAMUNIFORM1DEXTPROC                         glgenProgramUniform1dEXT;
extern PFNGLPROGRAMUNIFORM1DVPROC                           glgenProgramUniform1dv;
extern PFNGLPROGRAMUNIFORM1DVEXTPROC                        glgenProgramUniform1dvEXT;
extern PFNGLPROGRAMUNIFORM1FPROC                            glgenProgramUniform1f;
extern PFNGLPROGRAMUNIFORM1FEXTPROC                         glgenProgramUniform1fEXT;
extern PFNGLPROGRAMUNIFORM1FVPROC                           glgenProgramUniform1fv;
extern PFNGLPROGRAMUNIFORM1FVEXTPROC                        glgenProgramUniform1fvEXT;
extern PFNGLPROGRAMUNIFORM1IPROC                            glgenProgramUniform1i;
extern PFNGLPROGRAMUNIFORM1I64ARBPROC                       glgenProgramUniform1i64ARB;
extern PFNGLPROGRAMUNIFORM1I64NVPROC                        glgenProgramUniform1i64NV;
extern PFNGLPROGRAMUNIFORM1I64VARBPROC                      glgenProgramUniform1i64vARB;
extern PFNGLPROGRAMUNIFORM1I64VNVPROC                       glgenProgramUniform1i64vNV;
extern PFNGLPROGRAMUNIFORM1IEXTPROC                         glgenProgramUniform1iEXT;
extern PFNGLPROGRAMUNIFORM1IVPROC                           glgenProgramUniform1iv;
extern PFNGLPROGRAMUNIFORM1IVEXTPROC                        glgenProgramUniform1ivEXT;
extern PFNGLPROGRAMUNIFORM1UIPROC                           glgenProgramUniform1ui;
extern PFNGLPROGRAMUNIFORM1UI64ARBPROC                      glgenProgramUniform1ui64ARB;
extern PFNGLPROGRAMUNIFORM1UI64NVPROC                       glgenProgramUniform1ui64NV;
extern PFNGLPROGRAMUNIFORM1UI64VARBPROC                     glgenProgramUniform1ui64vARB;
extern PFNGLPROGRAMUNIFORM1UI64VNVPROC                      glgenProgramUniform1ui64vNV;
extern PFNGLPROGRAMUNIFORM1UIEXTPROC                        glgenProgramUniform1uiEXT;
extern PFNGLPROGRAMUNIFORM1UIVPROC                          glgenProgramUniform1uiv;
extern PFNGLPROGRAMUNIFORM1UIVEXTPROC                       glgenProgramUniform1uivEXT;
extern PFNGLPROGRAMUNIFORM2DPROC                            glgenProgramUniform2d;
extern PFNGLPROGRAMUNIFORM2DEXTPROC                         glgenProgramUniform2dEXT;
extern PFNGLPROGRAMUNIFORM2DVPROC                           glgenProgramUniform2dv;
extern PFNGLPROGRAMUNIFORM2DVEXTPROC                        glgenProgramUniform2dvEXT;
extern PFNGLPROGRAMUNIFORM2FPROC                            glgenProgramUniform2f;
extern PFNGLPROGRAMUNIFORM2FEXTPROC                         glgenProgramUniform2fEXT;
extern PFNGLPROGRAMUNIFORM2FVPROC                           glgenProgramUniform2fv;
extern PFNGLPROGRAMUNIFORM2FVEXTPROC                        glgenProgramUniform2fvEXT;
extern PFNGLPROGRAMUNIFORM2IPROC                            glgenProgramUniform2i;
extern PFNGLPROGRAMUNIFORM2I64ARBPROC                       glgenProgramUniform2i64ARB;
extern PFNGLPROGRAMUNIFORM2I64NVPROC                        glgenProgramUniform2i64NV;
extern PFNGLPROGRAMUNIFORM2I64VARBPROC                      glgenProgramUniform2i64vARB;
extern PFNGLPROGRAMUNIFORM2I64VNVPROC                       glgenProgramUniform2i64vNV;
extern PFNGLPROGRAMUNIFORM2IEXTPROC                         glgenProgramUniform2iEXT;
extern PFNGLPROGRAMUNIFORM2IVPROC                           glgenProgramUniform2iv;
extern PFNGLPROGRAMUNIFORM2IVEXTPROC                        glgenProgramUniform2ivEXT;
extern PFNGLPROGRAMUNIFORM2UIPROC                           glgenProgramUniform2ui;
extern PFNGLPROGRAMUNIFORM2UI64ARBPROC                      glgenProgramUniform2ui64ARB;
extern PFNGLPROGRAMUNIFORM2UI64NVPROC                       glgenProgramUniform2ui64NV;
extern PFNGLPROGRAMUNIFORM2UI64VARBPROC                     glgenProgramUniform2ui64vARB;
extern PFNGLPROGRAMUNIFORM2UI64VNVPROC                      glgenProgramUniform2ui64vNV;
extern PFNGLPROGRAMUNIFORM2UIEXTPROC                        glgenProgramUniform2uiEXT;
extern PFNGLPROGRAMUNIFORM2UIVPROC                          glgenProgramUniform2uiv;
extern PFNGLPROGRAMUNIFORM2UIVEXTPROC                       glgenProgramUniform2uivEXT;
extern PFNGLPROGRAMUNIFORM3DPROC                            glgenProgramUniform3d;
extern PFNGLPROGRAMUNIFORM3DEXTPROC                         glgenProgramUniform3dEXT;
extern PFNGLPROGRAMUNIFORM3DVPROC                           glgenProgramUniform3dv;
extern PFNGLPROGRAMUNIFORM3DVEXTPROC                        glgenProgramUniform3dvEXT;
extern PFNGLPROGRAMUNIFORM3FPROC                            glgenProgramUniform3f;
extern PFNGLPROGRAMUNIFORM3FEXTPROC                         glgenProgramUniform3fEXT;
extern PFNGLPROGRAMUNIFORM3FVPROC                           glgenProgramUniform3fv;
extern PFNGLPROGRAMUNIFORM3FVEXTPROC                        glgenProgramUniform3fvEXT;
extern PFNGLPROGRAMUNIFORM3IPROC                            glgenProgramUniform3i;
extern PFNGLPROGRAMUNIFORM3I64ARBPROC                       glgenProgramUniform3i64ARB;
extern PFNGLPROGRAMUNIFORM3I64NVPROC                        glgenProgramUniform3i64NV;
extern PFNGLPROGRAMUNIFORM3I64VARBPROC                      glgenProgramUniform3i64vARB;
extern PFNGLPROGRAMUNIFORM3I64VNVPROC                       glgenProgramUniform3i64vNV;
extern PFNGLPROGRAMUNIFORM3IEXTPROC                         glgenProgramUniform3iEXT;
extern PFNGLPROGRAMUNIFORM3IVPROC                           glgenProgramUniform3iv;
extern PFNGLPROGRAMUNIFORM3IVEXTPROC                        glgenProgramUniform3ivEXT;
extern PFNGLPROGRAMUNIFORM3UIPROC                           glgenProgramUniform3ui;
extern PFNGLPROGRAMUNIFORM3UI64ARBPROC                      glgenProgramUniform3ui64ARB;
extern PFNGLPROGRAMUNIFORM3UI64NVPROC                       glgenProgramUniform3ui64NV;
extern PFNGLPROGRAMUNIFORM3UI64VARBPROC                     glgenProgramUniform3ui64vARB;
extern PFNGLPROGRAMUNIFORM3UI64VNVPROC                      glgenProgramUniform3ui64vNV;
extern PFNGLPROGRAMUNIFORM3UIEXTPROC                        glgenProgramUniform3uiEXT;
extern PFNGLPROGRAMUNIFORM3UIVPROC                          glgenProgramUniform3uiv;
extern PFNGLPROGRAMUNIFORM3UIVEXTPROC                       glgenProgramUniform3uivEXT;
extern PFNGLPROGRAMUNIFORM4DPROC                            glgenProgramUniform4d;
extern PFNGLPROGRAMUNIFORM4DEXTPROC                         glgenProgramUniform4dEXT;
extern PFNGLPROGRAMUNIFORM4DVPROC                           glgenProgramUniform4dv;
extern PFNGLPROGRAMUNIFORM4DVEXTPROC                        glgenProgramUniform4dvEXT;
extern PFNGLPROGRAMUNIFORM4FPROC                            glgenProgramUniform4f;
extern PFNGLPROGRAMUNIFORM4FEXTPROC                         glgenProgramUniform4fEXT;
extern PFNGLPROGRAMUNIFORM4FVPROC                           glgenProgramUniform4fv;
extern PFNGLPROGRAMUNIFORM4FVEXTPROC                        glgenProgramUniform4fvEXT;
extern PFNGLPROGRAMUNIFORM4IPROC                            glgenProgramUniform4i;
extern PFNGLPROGRAMUNIFORM4I64ARBPROC                       glgenProgramUniform4i64ARB;
extern PFNGLPROGRAMUNIFORM4I64NVPROC                        glgenProgramUniform4i64NV;
extern PFNGLPROGRAMUNIFORM4I64VARBPROC                      glgenProgramUniform4i64vARB;
extern PFNGLPROGRAMUNIFORM4I64VNVPROC                       glgenProgramUniform4i64vNV;
extern PFNGLPROGRAMUNIFORM4IEXTPROC                         glgenProgramUniform4iEXT;
extern PFNGLPROGRAMUNIFORM4IVPROC                           glgenProgramUniform4iv;
extern PFNGLPROGRAMUNIFORM4IVEXTPROC                        glgenProgramUniform4ivEXT;
extern PFNGLPROGRAMUNIFORM4UIPROC                           glgenProgramUniform4ui;
extern PFNGLPROGRAMUNIFORM4UI64ARBPROC                      glgenProgramUniform4ui64ARB;
extern PFNGLPROGRAMUNIFORM4UI64NVPROC                       glgenProgramUniform4ui64NV;
extern PFNGLPROGRAMUNIFORM4UI64VARBPROC                     glgenProgramUniform4ui64vARB;
extern PFNGLPROGRAMUNIFORM4UI64VNVPROC                      glgenProgramUniform4ui64vNV;
extern PFNGLPROGRAMUNIFORM4UIEXTPROC                        glgenProgramUniform4uiEXT;
extern PFNGLPROGRAMUNIFORM4UIVPROC                          glgenProgramUniform4uiv;
extern PFNGLPROGRAMUNIFORM4UIVEXTPROC                       glgenProgramUniform4uivEXT;
extern PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC                 glgenProgramUniformHandleui64ARB;
extern PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC                  glgenProgramUniformHandleui64NV;
extern PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC                glgenProgramUniformHandleui64vARB;
extern PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC                 glgenProgramUniformHandleui64vNV;
extern PFNGLPROGRAMUNIFORMMATRIX2DVPROC                     glgenProgramUniformMatrix2dv;
extern PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC                  glgenProgramUniformMatrix2dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC                     glgenProgramUniformMatrix2fv;
extern PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC                  glgenProgramUniformMatrix2fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC                   glgenProgramUniformMatrix2x3dv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC                glgenProgramUniformMatrix2x3dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC                   glgenProgramUniformMatrix2x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC                glgenProgramUniformMatrix2x3fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC                   glgenProgramUniformMatrix2x4dv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC                glgenProgramUniformMatrix2x4dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC                   glgenProgramUniformMatrix2x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC                glgenProgramUniformMatrix2x4fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3DVPROC                     glgenProgramUniformMatrix3dv;
extern PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC                  glgenProgramUniformMatrix3dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC                     glgenProgramUniformMatrix3fv;
extern PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC                  glgenProgramUniformMatrix3fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC                   glgenProgramUniformMatrix3x2dv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC                glgenProgramUniformMatrix3x2dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC                   glgenProgramUniformMatrix3x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC                glgenProgramUniformMatrix3x2fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC                   glgenProgramUniformMatrix3x4dv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC                glgenProgramUniformMatrix3x4dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC                   glgenProgramUniformMatrix3x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC                glgenProgramUniformMatrix3x4fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4DVPROC                     glgenProgramUniformMatrix4dv;
extern PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC                  glgenProgramUniformMatrix4dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC                     glgenProgramUniformMatrix4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC                  glgenProgramUniformMatrix4fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC                   glgenProgramUniformMatrix4x2dv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC                glgenProgramUniformMatrix4x2dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC                   glgenProgramUniformMatrix4x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC                glgenProgramUniformMatrix4x2fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC                   glgenProgramUniformMatrix4x3dv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC                glgenProgramUniformMatrix4x3dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC                   glgenProgramUniformMatrix4x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC                glgenProgramUniformMatrix4x3fvEXT;
extern PFNGLPROGRAMUNIFORMUI64NVPROC                        glgenProgramUniformui64NV;
extern PFNGLPROGRAMUNIFORMUI64VNVPROC                       glgenProgramUniformui64vNV;
extern PFNGLPROVOKINGVERTEXPROC                             glgenProvokingVertex;
extern PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC                  glgenPushClientAttribDefaultEXT;
extern PFNGLPUSHDEBUGGROUPPROC                              glgenPushDebugGroup;
extern PFNGLPUSHGROUPMARKEREXTPROC                          glgenPushGroupMarkerEXT;
extern PFNGLQUERYCOUNTERPROC                                glgenQueryCounter;
extern PFNGLRASTERSAMPLESEXTPROC                            glgenRasterSamplesEXT;
extern PFNGLREADBUFFERPROC                                  glgenReadBuffer;
extern PFNGLREADPIXELSPROC                                  glgenReadPixels;
extern PFNGLREADNPIXELSPROC                                 glgenReadnPixels;
extern PFNGLREADNPIXELSARBPROC                              glgenReadnPixelsARB;
extern PFNGLRELEASESHADERCOMPILERPROC                       glgenReleaseShaderCompiler;
extern PFNGLRENDERBUFFERSTORAGEPROC                         glgenRenderbufferStorage;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC              glgenRenderbufferStorageMultisample;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC   glgenRenderbufferStorageMultisampleAdvancedAMD;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC    glgenRenderbufferStorageMultisampleCoverageNV;
extern PFNGLRESETMEMORYOBJECTPARAMETERNVPROC                glgenResetMemoryObjectParameterNV;
extern PFNGLRESOLVEDEPTHVALUESNVPROC                        glgenResolveDepthValuesNV;
extern PFNGLRESUMETRANSFORMFEEDBACKPROC                     glgenResumeTransformFeedback;
extern PFNGLSAMPLECOVERAGEPROC                              glgenSampleCoverage;
extern PFNGLSAMPLEMASKIPROC                                 glgenSampleMaski;
extern PFNGLSAMPLERPARAMETERIIVPROC                         glgenSamplerParameterIiv;
extern PFNGLSAMPLERPARAMETERIUIVPROC                        glgenSamplerParameterIuiv;
extern PFNGLSAMPLERPARAMETERFPROC                           glgenSamplerParameterf;
extern PFNGLSAMPLERPARAMETERFVPROC                          glgenSamplerParameterfv;
extern PFNGLSAMPLERPARAMETERIPROC                           glgenSamplerParameteri;
extern PFNGLSAMPLERPARAMETERIVPROC                          glgenSamplerParameteriv;
extern PFNGLSCISSORPROC                                     glgenScissor;
extern PFNGLSCISSORARRAYVPROC                               glgenScissorArrayv;
extern PFNGLSCISSOREXCLUSIVEARRAYVNVPROC                    glgenScissorExclusiveArrayvNV;
extern PFNGLSCISSOREXCLUSIVENVPROC                          glgenScissorExclusiveNV;
extern PFNGLSCISSORINDEXEDPROC                              glgenScissorIndexed;
extern PFNGLSCISSORINDEXEDVPROC                             glgenScissorIndexedv;
extern PFNGLSECONDARYCOLORFORMATNVPROC                      glgenSecondaryColorFormatNV;
extern PFNGLSELECTPERFMONITORCOUNTERSAMDPROC                glgenSelectPerfMonitorCountersAMD;
extern PFNGLSHADERBINARYPROC                                glgenShaderBinary;
extern PFNGLSHADERSOURCEPROC                                glgenShaderSource;
extern PFNGLSHADERSTORAGEBLOCKBINDINGPROC                   glgenShaderStorageBlockBinding;
extern PFNGLSHADINGRATEIMAGEBARRIERNVPROC                   glgenShadingRateImageBarrierNV;
extern PFNGLSHADINGRATEIMAGEPALETTENVPROC                   glgenShadingRateImagePaletteNV;
extern PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC              glgenShadingRateSampleOrderCustomNV;
extern PFNGLSHADINGRATESAMPLEORDERNVPROC                    glgenShadingRateSampleOrderNV;
extern PFNGLSIGNALVKFENCENVPROC                             glgenSignalVkFenceNV;
extern PFNGLSIGNALVKSEMAPHORENVPROC                         glgenSignalVkSemaphoreNV;
extern PFNGLSPECIALIZESHADERPROC                            glgenSpecializeShader;
extern PFNGLSPECIALIZESHADERARBPROC                         glgenSpecializeShaderARB;
extern PFNGLSTATECAPTURENVPROC                              glgenStateCaptureNV;
extern PFNGLSTENCILFILLPATHINSTANCEDNVPROC                  glgenStencilFillPathInstancedNV;
extern PFNGLSTENCILFILLPATHNVPROC                           glgenStencilFillPathNV;
extern PFNGLSTENCILFUNCPROC                                 glgenStencilFunc;
extern PFNGLSTENCILFUNCSEPARATEPROC                         glgenStencilFuncSeparate;
extern PFNGLSTENCILMASKPROC                                 glgenStencilMask;
extern PFNGLSTENCILMASKSEPARATEPROC                         glgenStencilMaskSeparate;
extern PFNGLSTENCILOPPROC                                   glgenStencilOp;
extern PFNGLSTENCILOPSEPARATEPROC                           glgenStencilOpSeparate;
extern PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC                glgenStencilStrokePathInstancedNV;
extern PFNGLSTENCILSTROKEPATHNVPROC                         glgenStencilStrokePathNV;
extern PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC         glgenStencilThenCoverFillPathInstancedNV;
extern PFNGLSTENCILTHENCOVERFILLPATHNVPROC                  glgenStencilThenCoverFillPathNV;
extern PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC       glgenStencilThenCoverStrokePathInstancedNV;
extern PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC                glgenStencilThenCoverStrokePathNV;
extern PFNGLSUBPIXELPRECISIONBIASNVPROC                     glgenSubpixelPrecisionBiasNV;
extern PFNGLTEXATTACHMEMORYNVPROC                           glgenTexAttachMemoryNV;
extern PFNGLTEXBUFFERPROC                                   glgenTexBuffer;
extern PFNGLTEXBUFFERARBPROC                                glgenTexBufferARB;
extern PFNGLTEXBUFFERRANGEPROC                              glgenTexBufferRange;
extern PFNGLTEXCOORDFORMATNVPROC                            glgenTexCoordFormatNV;
extern PFNGLTEXIMAGE1DPROC                                  glgenTexImage1D;
extern PFNGLTEXIMAGE2DPROC                                  glgenTexImage2D;
extern PFNGLTEXIMAGE2DMULTISAMPLEPROC                       glgenTexImage2DMultisample;
extern PFNGLTEXIMAGE3DPROC                                  glgenTexImage3D;
extern PFNGLTEXIMAGE3DMULTISAMPLEPROC                       glgenTexImage3DMultisample;
extern PFNGLTEXPAGECOMMITMENTARBPROC                        glgenTexPageCommitmentARB;
extern PFNGLTEXPARAMETERIIVPROC                             glgenTexParameterIiv;
extern PFNGLTEXPARAMETERIUIVPROC                            glgenTexParameterIuiv;
extern PFNGLTEXPARAMETERFPROC                               glgenTexParameterf;
extern PFNGLTEXPARAMETERFVPROC                              glgenTexParameterfv;
extern PFNGLTEXPARAMETERIPROC                               glgenTexParameteri;
extern PFNGLTEXPARAMETERIVPROC                              glgenTexParameteriv;
extern PFNGLTEXSTORAGE1DPROC                                glgenTexStorage1D;
extern PFNGLTEXSTORAGE2DPROC                                glgenTexStorage2D;
extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC                     glgenTexStorage2DMultisample;
extern PFNGLTEXSTORAGE3DPROC                                glgenTexStorage3D;
extern PFNGLTEXSTORAGE3DMULTISAMPLEPROC                     glgenTexStorage3DMultisample;
extern PFNGLTEXSUBIMAGE1DPROC                               glgenTexSubImage1D;
extern PFNGLTEXSUBIMAGE2DPROC                               glgenTexSubImage2D;
extern PFNGLTEXSUBIMAGE3DPROC                               glgenTexSubImage3D;
extern PFNGLTEXTUREATTACHMEMORYNVPROC                       glgenTextureAttachMemoryNV;
extern PFNGLTEXTUREBARRIERPROC                              glgenTextureBarrier;
extern PFNGLTEXTUREBARRIERNVPROC                            glgenTextureBarrierNV;
extern PFNGLTEXTUREBUFFERPROC                               glgenTextureBuffer;
extern PFNGLTEXTUREBUFFEREXTPROC                            glgenTextureBufferEXT;
extern PFNGLTEXTUREBUFFERRANGEPROC                          glgenTextureBufferRange;
extern PFNGLTEXTUREBUFFERRANGEEXTPROC                       glgenTextureBufferRangeEXT;
extern PFNGLTEXTUREIMAGE1DEXTPROC                           glgenTextureImage1DEXT;
extern PFNGLTEXTUREIMAGE2DEXTPROC                           glgenTextureImage2DEXT;
extern PFNGLTEXTUREIMAGE3DEXTPROC                           glgenTextureImage3DEXT;
extern PFNGLTEXTUREPAGECOMMITMENTEXTPROC                    glgenTexturePageCommitmentEXT;
extern PFNGLTEXTUREPARAMETERIIVPROC                         glgenTextureParameterIiv;
extern PFNGLTEXTUREPARAMETERIIVEXTPROC                      glgenTextureParameterIivEXT;
extern PFNGLTEXTUREPARAMETERIUIVPROC                        glgenTextureParameterIuiv;
extern PFNGLTEXTUREPARAMETERIUIVEXTPROC                     glgenTextureParameterIuivEXT;
extern PFNGLTEXTUREPARAMETERFPROC                           glgenTextureParameterf;
extern PFNGLTEXTUREPARAMETERFEXTPROC                        glgenTextureParameterfEXT;
extern PFNGLTEXTUREPARAMETERFVPROC                          glgenTextureParameterfv;
extern PFNGLTEXTUREPARAMETERFVEXTPROC                       glgenTextureParameterfvEXT;
extern PFNGLTEXTUREPARAMETERIPROC                           glgenTextureParameteri;
extern PFNGLTEXTUREPARAMETERIEXTPROC                        glgenTextureParameteriEXT;
extern PFNGLTEXTUREPARAMETERIVPROC                          glgenTextureParameteriv;
extern PFNGLTEXTUREPARAMETERIVEXTPROC                       glgenTextureParameterivEXT;
extern PFNGLTEXTURERENDERBUFFEREXTPROC                      glgenTextureRenderbufferEXT;
extern PFNGLTEXTURESTORAGE1DPROC                            glgenTextureStorage1D;
extern PFNGLTEXTURESTORAGE1DEXTPROC                         glgenTextureStorage1DEXT;
extern PFNGLTEXTURESTORAGE2DPROC                            glgenTextureStorage2D;
extern PFNGLTEXTURESTORAGE2DEXTPROC                         glgenTextureStorage2DEXT;
extern PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC                 glgenTextureStorage2DMultisample;
extern PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC              glgenTextureStorage2DMultisampleEXT;
extern PFNGLTEXTURESTORAGE3DPROC                            glgenTextureStorage3D;
extern PFNGLTEXTURESTORAGE3DEXTPROC                         glgenTextureStorage3DEXT;
extern PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC                 glgenTextureStorage3DMultisample;
extern PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC              glgenTextureStorage3DMultisampleEXT;
extern PFNGLTEXTURESUBIMAGE1DPROC                           glgenTextureSubImage1D;
extern PFNGLTEXTURESUBIMAGE1DEXTPROC                        glgenTextureSubImage1DEXT;
extern PFNGLTEXTURESUBIMAGE2DPROC                           glgenTextureSubImage2D;
extern PFNGLTEXTURESUBIMAGE2DEXTPROC                        glgenTextureSubImage2DEXT;
extern PFNGLTEXTURESUBIMAGE3DPROC                           glgenTextureSubImage3D;
extern PFNGLTEXTURESUBIMAGE3DEXTPROC                        glgenTextureSubImage3DEXT;
extern PFNGLTEXTUREVIEWPROC                                 glgenTextureView;
extern PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC                 glgenTransformFeedbackBufferBase;
extern PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC                glgenTransformFeedbackBufferRange;
extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC                   glgenTransformFeedbackVaryings;
extern PFNGLTRANSFORMPATHNVPROC                             glgenTransformPathNV;
extern PFNGLUNIFORM1DPROC                                   glgenUniform1d;
extern PFNGLUNIFORM1DVPROC                                  glgenUniform1dv;
extern PFNGLUNIFORM1FPROC                                   glgenUniform1f;
extern PFNGLUNIFORM1FVPROC                                  glgenUniform1fv;
extern PFNGLUNIFORM1IPROC                                   glgenUniform1i;
extern PFNGLUNIFORM1I64ARBPROC                              glgenUniform1i64ARB;
extern PFNGLUNIFORM1I64NVPROC                               glgenUniform1i64NV;
extern PFNGLUNIFORM1I64VARBPROC                             glgenUniform1i64vARB;
extern PFNGLUNIFORM1I64VNVPROC                              glgenUniform1i64vNV;
extern PFNGLUNIFORM1IVPROC                                  glgenUniform1iv;
extern PFNGLUNIFORM1UIPROC                                  glgenUniform1ui;
extern PFNGLUNIFORM1UI64ARBPROC                             glgenUniform1ui64ARB;
extern PFNGLUNIFORM1UI64NVPROC                              glgenUniform1ui64NV;
extern PFNGLUNIFORM1UI64VARBPROC                            glgenUniform1ui64vARB;
extern PFNGLUNIFORM1UI64VNVPROC                             glgenUniform1ui64vNV;
extern PFNGLUNIFORM1UIVPROC                                 glgenUniform1uiv;
extern PFNGLUNIFORM2DPROC                                   glgenUniform2d;
extern PFNGLUNIFORM2DVPROC                                  glgenUniform2dv;
extern PFNGLUNIFORM2FPROC                                   glgenUniform2f;
extern PFNGLUNIFORM2FVPROC                                  glgenUniform2fv;
extern PFNGLUNIFORM2IPROC                                   glgenUniform2i;
extern PFNGLUNIFORM2I64ARBPROC                              glgenUniform2i64ARB;
extern PFNGLUNIFORM2I64NVPROC                               glgenUniform2i64NV;
extern PFNGLUNIFORM2I64VARBPROC                             glgenUniform2i64vARB;
extern PFNGLUNIFORM2I64VNVPROC                              glgenUniform2i64vNV;
extern PFNGLUNIFORM2IVPROC                                  glgenUniform2iv;
extern PFNGLUNIFORM2UIPROC                                  glgenUniform2ui;
extern PFNGLUNIFORM2UI64ARBPROC                             glgenUniform2ui64ARB;
extern PFNGLUNIFORM2UI64NVPROC                              glgenUniform2ui64NV;
extern PFNGLUNIFORM2UI64VARBPROC                            glgenUniform2ui64vARB;
extern PFNGLUNIFORM2UI64VNVPROC                             glgenUniform2ui64vNV;
extern PFNGLUNIFORM2UIVPROC                                 glgenUniform2uiv;
extern PFNGLUNIFORM3DPROC                                   glgenUniform3d;
extern PFNGLUNIFORM3DVPROC                                  glgenUniform3dv;
extern PFNGLUNIFORM3FPROC                                   glgenUniform3f;
extern PFNGLUNIFORM3FVPROC                                  glgenUniform3fv;
extern PFNGLUNIFORM3IPROC                                   glgenUniform3i;
extern PFNGLUNIFORM3I64ARBPROC                              glgenUniform3i64ARB;
extern PFNGLUNIFORM3I64NVPROC                               glgenUniform3i64NV;
extern PFNGLUNIFORM3I64VARBPROC                             glgenUniform3i64vARB;
extern PFNGLUNIFORM3I64VNVPROC                              glgenUniform3i64vNV;
extern PFNGLUNIFORM3IVPROC                                  glgenUniform3iv;
extern PFNGLUNIFORM3UIPROC                                  glgenUniform3ui;
extern PFNGLUNIFORM3UI64ARBPROC                             glgenUniform3ui64ARB;
extern PFNGLUNIFORM3UI64NVPROC                              glgenUniform3ui64NV;
extern PFNGLUNIFORM3UI64VARBPROC                            glgenUniform3ui64vARB;
extern PFNGLUNIFORM3UI64VNVPROC                             glgenUniform3ui64vNV;
extern PFNGLUNIFORM3UIVPROC                                 glgenUniform3uiv;
extern PFNGLUNIFORM4DPROC                                   glgenUniform4d;
extern PFNGLUNIFORM4DVPROC                                  glgenUniform4dv;
extern PFNGLUNIFORM4FPROC                                   glgenUniform4f;
extern PFNGLUNIFORM4FVPROC                                  glgenUniform4fv;
extern PFNGLUNIFORM4IPROC                                   glgenUniform4i;
extern PFNGLUNIFORM4I64ARBPROC                              glgenUniform4i64ARB;
extern PFNGLUNIFORM4I64NVPROC                               glgenUniform4i64NV;
extern PFNGLUNIFORM4I64VARBPROC                             glgenUniform4i64vARB;
extern PFNGLUNIFORM4I64VNVPROC                              glgenUniform4i64vNV;
extern PFNGLUNIFORM4IVPROC                                  glgenUniform4iv;
extern PFNGLUNIFORM4UIPROC                                  glgenUniform4ui;
extern PFNGLUNIFORM4UI64ARBPROC                             glgenUniform4ui64ARB;
extern PFNGLUNIFORM4UI64NVPROC                              glgenUniform4ui64NV;
extern PFNGLUNIFORM4UI64VARBPROC                            glgenUniform4ui64vARB;
extern PFNGLUNIFORM4UI64VNVPROC                             glgenUniform4ui64vNV;
extern PFNGLUNIFORM4UIVPROC                                 glgenUniform4uiv;
extern PFNGLUNIFORMBLOCKBINDINGPROC                         glgenUniformBlockBinding;
extern PFNGLUNIFORMHANDLEUI64ARBPROC                        glgenUniformHandleui64ARB;
extern PFNGLUNIFORMHANDLEUI64NVPROC                         glgenUniformHandleui64NV;
extern PFNGLUNIFORMHANDLEUI64VARBPROC                       glgenUniformHandleui64vARB;
extern PFNGLUNIFORMHANDLEUI64VNVPROC                        glgenUniformHandleui64vNV;
extern PFNGLUNIFORMMATRIX2DVPROC                            glgenUniformMatrix2dv;
extern PFNGLUNIFORMMATRIX2FVPROC                            glgenUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX2X3DVPROC                          glgenUniformMatrix2x3dv;
extern PFNGLUNIFORMMATRIX2X3FVPROC                          glgenUniformMatrix2x3fv;
extern PFNGLUNIFORMMATRIX2X4DVPROC                          glgenUniformMatrix2x4dv;
extern PFNGLUNIFORMMATRIX2X4FVPROC                          glgenUniformMatrix2x4fv;
extern PFNGLUNIFORMMATRIX3DVPROC                            glgenUniformMatrix3dv;
extern PFNGLUNIFORMMATRIX3FVPROC                            glgenUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX3X2DVPROC                          glgenUniformMatrix3x2dv;
extern PFNGLUNIFORMMATRIX3X2FVPROC                          glgenUniformMatrix3x2fv;
extern PFNGLUNIFORMMATRIX3X4DVPROC                          glgenUniformMatrix3x4dv;
extern PFNGLUNIFORMMATRIX3X4FVPROC                          glgenUniformMatrix3x4fv;
extern PFNGLUNIFORMMATRIX4DVPROC                            glgenUniformMatrix4dv;
extern PFNGLUNIFORMMATRIX4FVPROC                            glgenUniformMatrix4fv;
extern PFNGLUNIFORMMATRIX4X2DVPROC                          glgenUniformMatrix4x2dv;
extern PFNGLUNIFORMMATRIX4X2FVPROC                          glgenUniformMatrix4x2fv;
extern PFNGLUNIFORMMATRIX4X3DVPROC                          glgenUniformMatrix4x3dv;
extern PFNGLUNIFORMMATRIX4X3FVPROC                          glgenUniformMatrix4x3fv;
extern PFNGLUNIFORMSUBROUTINESUIVPROC                       glgenUniformSubroutinesuiv;
extern PFNGLUNIFORMUI64NVPROC                               glgenUniformui64NV;
extern PFNGLUNIFORMUI64VNVPROC                              glgenUniformui64vNV;
extern PFNGLUNMAPBUFFERPROC                                 glgenUnmapBuffer;
extern PFNGLUNMAPNAMEDBUFFERPROC                            glgenUnmapNamedBuffer;
extern PFNGLUNMAPNAMEDBUFFEREXTPROC                         glgenUnmapNamedBufferEXT;
extern PFNGLUSEPROGRAMPROC                                  glgenUseProgram;
extern PFNGLUSEPROGRAMSTAGESPROC                            glgenUseProgramStages;
extern PFNGLUSESHADERPROGRAMEXTPROC                         glgenUseShaderProgramEXT;
extern PFNGLVALIDATEPROGRAMPROC                             glgenValidateProgram;
extern PFNGLVALIDATEPROGRAMPIPELINEPROC                     glgenValidateProgramPipeline;
extern PFNGLVERTEXARRAYATTRIBBINDINGPROC                    glgenVertexArrayAttribBinding;
extern PFNGLVERTEXARRAYATTRIBFORMATPROC                     glgenVertexArrayAttribFormat;
extern PFNGLVERTEXARRAYATTRIBIFORMATPROC                    glgenVertexArrayAttribIFormat;
extern PFNGLVERTEXARRAYATTRIBLFORMATPROC                    glgenVertexArrayAttribLFormat;
extern PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC              glgenVertexArrayBindVertexBufferEXT;
extern PFNGLVERTEXARRAYBINDINGDIVISORPROC                   glgenVertexArrayBindingDivisor;
extern PFNGLVERTEXARRAYCOLOROFFSETEXTPROC                   glgenVertexArrayColorOffsetEXT;
extern PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC                glgenVertexArrayEdgeFlagOffsetEXT;
extern PFNGLVERTEXARRAYELEMENTBUFFERPROC                    glgenVertexArrayElementBuffer;
extern PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC                glgenVertexArrayFogCoordOffsetEXT;
extern PFNGLVERTEXARRAYINDEXOFFSETEXTPROC                   glgenVertexArrayIndexOffsetEXT;
extern PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC           glgenVertexArrayMultiTexCoordOffsetEXT;
extern PFNGLVERTEXARRAYNORMALOFFSETEXTPROC                  glgenVertexArrayNormalOffsetEXT;
extern PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC          glgenVertexArraySecondaryColorOffsetEXT;
extern PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC                glgenVertexArrayTexCoordOffsetEXT;
extern PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC           glgenVertexArrayVertexAttribBindingEXT;
extern PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC           glgenVertexArrayVertexAttribDivisorEXT;
extern PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC            glgenVertexArrayVertexAttribFormatEXT;
extern PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC           glgenVertexArrayVertexAttribIFormatEXT;
extern PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC           glgenVertexArrayVertexAttribIOffsetEXT;
extern PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC           glgenVertexArrayVertexAttribLFormatEXT;
extern PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC           glgenVertexArrayVertexAttribLOffsetEXT;
extern PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC            glgenVertexArrayVertexAttribOffsetEXT;
extern PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC          glgenVertexArrayVertexBindingDivisorEXT;
extern PFNGLVERTEXARRAYVERTEXBUFFERPROC                     glgenVertexArrayVertexBuffer;
extern PFNGLVERTEXARRAYVERTEXBUFFERSPROC                    glgenVertexArrayVertexBuffers;
extern PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC                  glgenVertexArrayVertexOffsetEXT;
extern PFNGLVERTEXATTRIB1DPROC                              glgenVertexAttrib1d;
extern PFNGLVERTEXATTRIB1DVPROC                             glgenVertexAttrib1dv;
extern PFNGLVERTEXATTRIB1FPROC                              glgenVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC                             glgenVertexAttrib1fv;
extern PFNGLVERTEXATTRIB1SPROC                              glgenVertexAttrib1s;
extern PFNGLVERTEXATTRIB1SVPROC                             glgenVertexAttrib1sv;
extern PFNGLVERTEXATTRIB2DPROC                              glgenVertexAttrib2d;
extern PFNGLVERTEXATTRIB2DVPROC                             glgenVertexAttrib2dv;
extern PFNGLVERTEXATTRIB2FPROC                              glgenVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FVPROC                             glgenVertexAttrib2fv;
extern PFNGLVERTEXATTRIB2SPROC                              glgenVertexAttrib2s;
extern PFNGLVERTEXATTRIB2SVPROC                             glgenVertexAttrib2sv;
extern PFNGLVERTEXATTRIB3DPROC                              glgenVertexAttrib3d;
extern PFNGLVERTEXATTRIB3DVPROC                             glgenVertexAttrib3dv;
extern PFNGLVERTEXATTRIB3FPROC                              glgenVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FVPROC                             glgenVertexAttrib3fv;
extern PFNGLVERTEXATTRIB3SPROC                              glgenVertexAttrib3s;
extern PFNGLVERTEXATTRIB3SVPROC                             glgenVertexAttrib3sv;
extern PFNGLVERTEXATTRIB4NBVPROC                            glgenVertexAttrib4Nbv;
extern PFNGLVERTEXATTRIB4NIVPROC                            glgenVertexAttrib4Niv;
extern PFNGLVERTEXATTRIB4NSVPROC                            glgenVertexAttrib4Nsv;
extern PFNGLVERTEXATTRIB4NUBPROC                            glgenVertexAttrib4Nub;
extern PFNGLVERTEXATTRIB4NUBVPROC                           glgenVertexAttrib4Nubv;
extern PFNGLVERTEXATTRIB4NUIVPROC                           glgenVertexAttrib4Nuiv;
extern PFNGLVERTEXATTRIB4NUSVPROC                           glgenVertexAttrib4Nusv;
extern PFNGLVERTEXATTRIB4BVPROC                             glgenVertexAttrib4bv;
extern PFNGLVERTEXATTRIB4DPROC                              glgenVertexAttrib4d;
extern PFNGLVERTEXATTRIB4DVPROC                             glgenVertexAttrib4dv;
extern PFNGLVERTEXATTRIB4FPROC                              glgenVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC                             glgenVertexAttrib4fv;
extern PFNGLVERTEXATTRIB4IVPROC                             glgenVertexAttrib4iv;
extern PFNGLVERTEXATTRIB4SPROC                              glgenVertexAttrib4s;
extern PFNGLVERTEXATTRIB4SVPROC                             glgenVertexAttrib4sv;
extern PFNGLVERTEXATTRIB4UBVPROC                            glgenVertexAttrib4ubv;
extern PFNGLVERTEXATTRIB4UIVPROC                            glgenVertexAttrib4uiv;
extern PFNGLVERTEXATTRIB4USVPROC                            glgenVertexAttrib4usv;
extern PFNGLVERTEXATTRIBBINDINGPROC                         glgenVertexAttribBinding;
extern PFNGLVERTEXATTRIBDIVISORPROC                         glgenVertexAttribDivisor;
extern PFNGLVERTEXATTRIBDIVISORARBPROC                      glgenVertexAttribDivisorARB;
extern PFNGLVERTEXATTRIBFORMATPROC                          glgenVertexAttribFormat;
extern PFNGLVERTEXATTRIBFORMATNVPROC                        glgenVertexAttribFormatNV;
extern PFNGLVERTEXATTRIBI1IPROC                             glgenVertexAttribI1i;
extern PFNGLVERTEXATTRIBI1IVPROC                            glgenVertexAttribI1iv;
extern PFNGLVERTEXATTRIBI1UIPROC                            glgenVertexAttribI1ui;
extern PFNGLVERTEXATTRIBI1UIVPROC                           glgenVertexAttribI1uiv;
extern PFNGLVERTEXATTRIBI2IPROC                             glgenVertexAttribI2i;
extern PFNGLVERTEXATTRIBI2IVPROC                            glgenVertexAttribI2iv;
extern PFNGLVERTEXATTRIBI2UIPROC                            glgenVertexAttribI2ui;
extern PFNGLVERTEXATTRIBI2UIVPROC                           glgenVertexAttribI2uiv;
extern PFNGLVERTEXATTRIBI3IPROC                             glgenVertexAttribI3i;
extern PFNGLVERTEXATTRIBI3IVPROC                            glgenVertexAttribI3iv;
extern PFNGLVERTEXATTRIBI3UIPROC                            glgenVertexAttribI3ui;
extern PFNGLVERTEXATTRIBI3UIVPROC                           glgenVertexAttribI3uiv;
extern PFNGLVERTEXATTRIBI4BVPROC                            glgenVertexAttribI4bv;
extern PFNGLVERTEXATTRIBI4IPROC                             glgenVertexAttribI4i;
extern PFNGLVERTEXATTRIBI4IVPROC                            glgenVertexAttribI4iv;
extern PFNGLVERTEXATTRIBI4SVPROC                            glgenVertexAttribI4sv;
extern PFNGLVERTEXATTRIBI4UBVPROC                           glgenVertexAttribI4ubv;
extern PFNGLVERTEXATTRIBI4UIPROC                            glgenVertexAttribI4ui;
extern PFNGLVERTEXATTRIBI4UIVPROC                           glgenVertexAttribI4uiv;
extern PFNGLVERTEXATTRIBI4USVPROC                           glgenVertexAttribI4usv;
extern PFNGLVERTEXATTRIBIFORMATPROC                         glgenVertexAttribIFormat;
extern PFNGLVERTEXATTRIBIFORMATNVPROC                       glgenVertexAttribIFormatNV;
extern PFNGLVERTEXATTRIBIPOINTERPROC                        glgenVertexAttribIPointer;
extern PFNGLVERTEXATTRIBL1DPROC                             glgenVertexAttribL1d;
extern PFNGLVERTEXATTRIBL1DVPROC                            glgenVertexAttribL1dv;
extern PFNGLVERTEXATTRIBL1I64NVPROC                         glgenVertexAttribL1i64NV;
extern PFNGLVERTEXATTRIBL1I64VNVPROC                        glgenVertexAttribL1i64vNV;
extern PFNGLVERTEXATTRIBL1UI64ARBPROC                       glgenVertexAttribL1ui64ARB;
extern PFNGLVERTEXATTRIBL1UI64NVPROC                        glgenVertexAttribL1ui64NV;
extern PFNGLVERTEXATTRIBL1UI64VARBPROC                      glgenVertexAttribL1ui64vARB;
extern PFNGLVERTEXATTRIBL1UI64VNVPROC                       glgenVertexAttribL1ui64vNV;
extern PFNGLVERTEXATTRIBL2DPROC                             glgenVertexAttribL2d;
extern PFNGLVERTEXATTRIBL2DVPROC                            glgenVertexAttribL2dv;
extern PFNGLVERTEXATTRIBL2I64NVPROC                         glgenVertexAttribL2i64NV;
extern PFNGLVERTEXATTRIBL2I64VNVPROC                        glgenVertexAttribL2i64vNV;
extern PFNGLVERTEXATTRIBL2UI64NVPROC                        glgenVertexAttribL2ui64NV;
extern PFNGLVERTEXATTRIBL2UI64VNVPROC                       glgenVertexAttribL2ui64vNV;
extern PFNGLVERTEXATTRIBL3DPROC                             glgenVertexAttribL3d;
extern PFNGLVERTEXATTRIBL3DVPROC                            glgenVertexAttribL3dv;
extern PFNGLVERTEXATTRIBL3I64NVPROC                         glgenVertexAttribL3i64NV;
extern PFNGLVERTEXATTRIBL3I64VNVPROC                        glgenVertexAttribL3i64vNV;
extern PFNGLVERTEXATTRIBL3UI64NVPROC                        glgenVertexAttribL3ui64NV;
extern PFNGLVERTEXATTRIBL3UI64VNVPROC                       glgenVertexAttribL3ui64vNV;
extern PFNGLVERTEXATTRIBL4DPROC                             glgenVertexAttribL4d;
extern PFNGLVERTEXATTRIBL4DVPROC                            glgenVertexAttribL4dv;
extern PFNGLVERTEXATTRIBL4I64NVPROC                         glgenVertexAttribL4i64NV;
extern PFNGLVERTEXATTRIBL4I64VNVPROC                        glgenVertexAttribL4i64vNV;
extern PFNGLVERTEXATTRIBL4UI64NVPROC                        glgenVertexAttribL4ui64NV;
extern PFNGLVERTEXATTRIBL4UI64VNVPROC                       glgenVertexAttribL4ui64vNV;
extern PFNGLVERTEXATTRIBLFORMATPROC                         glgenVertexAttribLFormat;
extern PFNGLVERTEXATTRIBLFORMATNVPROC                       glgenVertexAttribLFormatNV;
extern PFNGLVERTEXATTRIBLPOINTERPROC                        glgenVertexAttribLPointer;
extern PFNGLVERTEXATTRIBP1UIPROC                            glgenVertexAttribP1ui;
extern PFNGLVERTEXATTRIBP1UIVPROC                           glgenVertexAttribP1uiv;
extern PFNGLVERTEXATTRIBP2UIPROC                            glgenVertexAttribP2ui;
extern PFNGLVERTEXATTRIBP2UIVPROC                           glgenVertexAttribP2uiv;
extern PFNGLVERTEXATTRIBP3UIPROC                            glgenVertexAttribP3ui;
extern PFNGLVERTEXATTRIBP3UIVPROC                           glgenVertexAttribP3uiv;
extern PFNGLVERTEXATTRIBP4UIPROC                            glgenVertexAttribP4ui;
extern PFNGLVERTEXATTRIBP4UIVPROC                           glgenVertexAttribP4uiv;
extern PFNGLVERTEXATTRIBPOINTERPROC                         glgenVertexAttribPointer;
extern PFNGLVERTEXBINDINGDIVISORPROC                        glgenVertexBindingDivisor;
extern PFNGLVERTEXFORMATNVPROC                              glgenVertexFormatNV;
extern PFNGLVIEWPORTPROC                                    glgenViewport;
extern PFNGLVIEWPORTARRAYVPROC                              glgenViewportArrayv;
extern PFNGLVIEWPORTINDEXEDFPROC                            glgenViewportIndexedf;
extern PFNGLVIEWPORTINDEXEDFVPROC                           glgenViewportIndexedfv;
extern PFNGLVIEWPORTPOSITIONWSCALENVPROC                    glgenViewportPositionWScaleNV;
extern PFNGLVIEWPORTSWIZZLENVPROC                           glgenViewportSwizzleNV;
extern PFNGLWAITSYNCPROC                                    glgenWaitSync;
extern PFNGLWAITVKSEMAPHORENVPROC                           glgenWaitVkSemaphoreNV;
extern PFNGLWEIGHTPATHSNVPROC                               glgenWeightPathsNV;
extern PFNGLWINDOWRECTANGLESEXTPROC                         glgenWindowRectanglesEXT;

#define glActiveProgramEXT                            glgenActiveProgramEXT
#define glActiveShaderProgram                         glgenActiveShaderProgram
#define glActiveTexture                               glgenActiveTexture
#define glApplyFramebufferAttachmentCMAAINTEL         glgenApplyFramebufferAttachmentCMAAINTEL
#define glAttachShader                                glgenAttachShader
#define glBeginConditionalRender                      glgenBeginConditionalRender
#define glBeginConditionalRenderNV                    glgenBeginConditionalRenderNV
#define glBeginPerfMonitorAMD                         glgenBeginPerfMonitorAMD
#define glBeginPerfQueryINTEL                         glgenBeginPerfQueryINTEL
#define glBeginQuery                                  glgenBeginQuery
#define glBeginQueryIndexed                           glgenBeginQueryIndexed
#define glBeginTransformFeedback                      glgenBeginTransformFeedback
#define glBindAttribLocation                          glgenBindAttribLocation
#define glBindBuffer                                  glgenBindBuffer
#define glBindBufferBase                              glgenBindBufferBase
#define glBindBufferRange                             glgenBindBufferRange
#define glBindBuffersBase                             glgenBindBuffersBase
#define glBindBuffersRange                            glgenBindBuffersRange
#define glBindFragDataLocation                        glgenBindFragDataLocation
#define glBindFragDataLocationIndexed                 glgenBindFragDataLocationIndexed
#define glBindFramebuffer                             glgenBindFramebuffer
#define glBindImageTexture                            glgenBindImageTexture
#define glBindImageTextures                           glgenBindImageTextures
#define glBindMultiTextureEXT                         glgenBindMultiTextureEXT
#define glBindProgramPipeline                         glgenBindProgramPipeline
#define glBindRenderbuffer                            glgenBindRenderbuffer
#define glBindSampler                                 glgenBindSampler
#define glBindSamplers                                glgenBindSamplers
#define glBindShadingRateImageNV                      glgenBindShadingRateImageNV
#define glBindTexture                                 glgenBindTexture
#define glBindTextureUnit                             glgenBindTextureUnit
#define glBindTextures                                glgenBindTextures
#define glBindTransformFeedback                       glgenBindTransformFeedback
#define glBindVertexArray                             glgenBindVertexArray
#define glBindVertexBuffer                            glgenBindVertexBuffer
#define glBindVertexBuffers                           glgenBindVertexBuffers
#define glBlendBarrierKHR                             glgenBlendBarrierKHR
#define glBlendBarrierNV                              glgenBlendBarrierNV
#define glBlendColor                                  glgenBlendColor
#define glBlendEquation                               glgenBlendEquation
#define glBlendEquationSeparate                       glgenBlendEquationSeparate
#define glBlendEquationSeparatei                      glgenBlendEquationSeparatei
#define glBlendEquationSeparateiARB                   glgenBlendEquationSeparateiARB
#define glBlendEquationi                              glgenBlendEquationi
#define glBlendEquationiARB                           glgenBlendEquationiARB
#define glBlendFunc                                   glgenBlendFunc
#define glBlendFuncSeparate                           glgenBlendFuncSeparate
#define glBlendFuncSeparatei                          glgenBlendFuncSeparatei
#define glBlendFuncSeparateiARB                       glgenBlendFuncSeparateiARB
#define glBlendFunci                                  glgenBlendFunci
#define glBlendFunciARB                               glgenBlendFunciARB
#define glBlendParameteriNV                           glgenBlendParameteriNV
#define glBlitFramebuffer                             glgenBlitFramebuffer
#define glBlitNamedFramebuffer                        glgenBlitNamedFramebuffer
#define glBufferAddressRangeNV                        glgenBufferAddressRangeNV
#define glBufferAttachMemoryNV                        glgenBufferAttachMemoryNV
#define glBufferData                                  glgenBufferData
#define glBufferPageCommitmentARB                     glgenBufferPageCommitmentARB
#define glBufferStorage                               glgenBufferStorage
#define glBufferSubData                               glgenBufferSubData
#define glCallCommandListNV                           glgenCallCommandListNV
#define glCheckFramebufferStatus                      glgenCheckFramebufferStatus
#define glCheckNamedFramebufferStatus                 glgenCheckNamedFramebufferStatus
#define glCheckNamedFramebufferStatusEXT              glgenCheckNamedFramebufferStatusEXT
#define glClampColor                                  glgenClampColor
#define glClear                                       glgenClear
#define glClearBufferData                             glgenClearBufferData
#define glClearBufferSubData                          glgenClearBufferSubData
#define glClearBufferfi                               glgenClearBufferfi
#define glClearBufferfv                               glgenClearBufferfv
#define glClearBufferiv                               glgenClearBufferiv
#define glClearBufferuiv                              glgenClearBufferuiv
#define glClearColor                                  glgenClearColor
#define glClearDepth                                  glgenClearDepth
#define glClearDepthf                                 glgenClearDepthf
#define glClearNamedBufferData                        glgenClearNamedBufferData
#define glClearNamedBufferDataEXT                     glgenClearNamedBufferDataEXT
#define glClearNamedBufferSubData                     glgenClearNamedBufferSubData
#define glClearNamedBufferSubDataEXT                  glgenClearNamedBufferSubDataEXT
#define glClearNamedFramebufferfi                     glgenClearNamedFramebufferfi
#define glClearNamedFramebufferfv                     glgenClearNamedFramebufferfv
#define glClearNamedFramebufferiv                     glgenClearNamedFramebufferiv
#define glClearNamedFramebufferuiv                    glgenClearNamedFramebufferuiv
#define glClearStencil                                glgenClearStencil
#define glClearTexImage                               glgenClearTexImage
#define glClearTexSubImage                            glgenClearTexSubImage
#define glClientAttribDefaultEXT                      glgenClientAttribDefaultEXT
#define glClientWaitSync                              glgenClientWaitSync
#define glClipControl                                 glgenClipControl
#define glColorFormatNV                               glgenColorFormatNV
#define glColorMask                                   glgenColorMask
#define glColorMaski                                  glgenColorMaski
#define glCommandListSegmentsNV                       glgenCommandListSegmentsNV
#define glCompileCommandListNV                        glgenCompileCommandListNV
#define glCompileShader                               glgenCompileShader
#define glCompileShaderIncludeARB                     glgenCompileShaderIncludeARB
#define glCompressedMultiTexImage1DEXT                glgenCompressedMultiTexImage1DEXT
#define glCompressedMultiTexImage2DEXT                glgenCompressedMultiTexImage2DEXT
#define glCompressedMultiTexImage3DEXT                glgenCompressedMultiTexImage3DEXT
#define glCompressedMultiTexSubImage1DEXT             glgenCompressedMultiTexSubImage1DEXT
#define glCompressedMultiTexSubImage2DEXT             glgenCompressedMultiTexSubImage2DEXT
#define glCompressedMultiTexSubImage3DEXT             glgenCompressedMultiTexSubImage3DEXT
#define glCompressedTexImage1D                        glgenCompressedTexImage1D
#define glCompressedTexImage2D                        glgenCompressedTexImage2D
#define glCompressedTexImage3D                        glgenCompressedTexImage3D
#define glCompressedTexSubImage1D                     glgenCompressedTexSubImage1D
#define glCompressedTexSubImage2D                     glgenCompressedTexSubImage2D
#define glCompressedTexSubImage3D                     glgenCompressedTexSubImage3D
#define glCompressedTextureImage1DEXT                 glgenCompressedTextureImage1DEXT
#define glCompressedTextureImage2DEXT                 glgenCompressedTextureImage2DEXT
#define glCompressedTextureImage3DEXT                 glgenCompressedTextureImage3DEXT
#define glCompressedTextureSubImage1D                 glgenCompressedTextureSubImage1D
#define glCompressedTextureSubImage1DEXT              glgenCompressedTextureSubImage1DEXT
#define glCompressedTextureSubImage2D                 glgenCompressedTextureSubImage2D
#define glCompressedTextureSubImage2DEXT              glgenCompressedTextureSubImage2DEXT
#define glCompressedTextureSubImage3D                 glgenCompressedTextureSubImage3D
#define glCompressedTextureSubImage3DEXT              glgenCompressedTextureSubImage3DEXT
#define glConservativeRasterParameterfNV              glgenConservativeRasterParameterfNV
#define glConservativeRasterParameteriNV              glgenConservativeRasterParameteriNV
#define glCopyBufferSubData                           glgenCopyBufferSubData
#define glCopyImageSubData                            glgenCopyImageSubData
#define glCopyMultiTexImage1DEXT                      glgenCopyMultiTexImage1DEXT
#define glCopyMultiTexImage2DEXT                      glgenCopyMultiTexImage2DEXT
#define glCopyMultiTexSubImage1DEXT                   glgenCopyMultiTexSubImage1DEXT
#define glCopyMultiTexSubImage2DEXT                   glgenCopyMultiTexSubImage2DEXT
#define glCopyMultiTexSubImage3DEXT                   glgenCopyMultiTexSubImage3DEXT
#define glCopyNamedBufferSubData                      glgenCopyNamedBufferSubData
#define glCopyPathNV                                  glgenCopyPathNV
#define glCopyTexImage1D                              glgenCopyTexImage1D
#define glCopyTexImage2D                              glgenCopyTexImage2D
#define glCopyTexSubImage1D                           glgenCopyTexSubImage1D
#define glCopyTexSubImage2D                           glgenCopyTexSubImage2D
#define glCopyTexSubImage3D                           glgenCopyTexSubImage3D
#define glCopyTextureImage1DEXT                       glgenCopyTextureImage1DEXT
#define glCopyTextureImage2DEXT                       glgenCopyTextureImage2DEXT
#define glCopyTextureSubImage1D                       glgenCopyTextureSubImage1D
#define glCopyTextureSubImage1DEXT                    glgenCopyTextureSubImage1DEXT
#define glCopyTextureSubImage2D                       glgenCopyTextureSubImage2D
#define glCopyTextureSubImage2DEXT                    glgenCopyTextureSubImage2DEXT
#define glCopyTextureSubImage3D                       glgenCopyTextureSubImage3D
#define glCopyTextureSubImage3DEXT                    glgenCopyTextureSubImage3DEXT
#define glCoverFillPathInstancedNV                    glgenCoverFillPathInstancedNV
#define glCoverFillPathNV                             glgenCoverFillPathNV
#define glCoverStrokePathInstancedNV                  glgenCoverStrokePathInstancedNV
#define glCoverStrokePathNV                           glgenCoverStrokePathNV
#define glCoverageModulationNV                        glgenCoverageModulationNV
#define glCoverageModulationTableNV                   glgenCoverageModulationTableNV
#define glCreateBuffers                               glgenCreateBuffers
#define glCreateCommandListsNV                        glgenCreateCommandListsNV
#define glCreateFramebuffers                          glgenCreateFramebuffers
#define glCreatePerfQueryINTEL                        glgenCreatePerfQueryINTEL
#define glCreateProgram                               glgenCreateProgram
#define glCreateProgramPipelines                      glgenCreateProgramPipelines
#define glCreateQueries                               glgenCreateQueries
#define glCreateRenderbuffers                         glgenCreateRenderbuffers
#define glCreateSamplers                              glgenCreateSamplers
#define glCreateShader                                glgenCreateShader
#define glCreateShaderProgramEXT                      glgenCreateShaderProgramEXT
#define glCreateShaderProgramv                        glgenCreateShaderProgramv
#define glCreateStatesNV                              glgenCreateStatesNV
#define glCreateSyncFromCLeventARB                    glgenCreateSyncFromCLeventARB
#define glCreateTextures                              glgenCreateTextures
#define glCreateTransformFeedbacks                    glgenCreateTransformFeedbacks
#define glCreateVertexArrays                          glgenCreateVertexArrays
#define glCullFace                                    glgenCullFace
#define glDebugMessageCallback                        glgenDebugMessageCallback
#define glDebugMessageCallbackARB                     glgenDebugMessageCallbackARB
#define glDebugMessageControl                         glgenDebugMessageControl
#define glDebugMessageControlARB                      glgenDebugMessageControlARB
#define glDebugMessageInsert                          glgenDebugMessageInsert
#define glDebugMessageInsertARB                       glgenDebugMessageInsertARB
#define glDeleteBuffers                               glgenDeleteBuffers
#define glDeleteCommandListsNV                        glgenDeleteCommandListsNV
#define glDeleteFramebuffers                          glgenDeleteFramebuffers
#define glDeleteNamedStringARB                        glgenDeleteNamedStringARB
#define glDeletePathsNV                               glgenDeletePathsNV
#define glDeletePerfMonitorsAMD                       glgenDeletePerfMonitorsAMD
#define glDeletePerfQueryINTEL                        glgenDeletePerfQueryINTEL
#define glDeleteProgram                               glgenDeleteProgram
#define glDeleteProgramPipelines                      glgenDeleteProgramPipelines
#define glDeleteQueries                               glgenDeleteQueries
#define glDeleteRenderbuffers                         glgenDeleteRenderbuffers
#define glDeleteSamplers                              glgenDeleteSamplers
#define glDeleteShader                                glgenDeleteShader
#define glDeleteStatesNV                              glgenDeleteStatesNV
#define glDeleteSync                                  glgenDeleteSync
#define glDeleteTextures                              glgenDeleteTextures
#define glDeleteTransformFeedbacks                    glgenDeleteTransformFeedbacks
#define glDeleteVertexArrays                          glgenDeleteVertexArrays
#define glDepthFunc                                   glgenDepthFunc
#define glDepthMask                                   glgenDepthMask
#define glDepthRange                                  glgenDepthRange
#define glDepthRangeArrayv                            glgenDepthRangeArrayv
#define glDepthRangeIndexed                           glgenDepthRangeIndexed
#define glDepthRangef                                 glgenDepthRangef
#define glDetachShader                                glgenDetachShader
#define glDisable                                     glgenDisable
#define glDisableClientStateIndexedEXT                glgenDisableClientStateIndexedEXT
#define glDisableClientStateiEXT                      glgenDisableClientStateiEXT
#define glDisableIndexedEXT                           glgenDisableIndexedEXT
#define glDisableVertexArrayAttrib                    glgenDisableVertexArrayAttrib
#define glDisableVertexArrayAttribEXT                 glgenDisableVertexArrayAttribEXT
#define glDisableVertexArrayEXT                       glgenDisableVertexArrayEXT
#define glDisableVertexAttribArray                    glgenDisableVertexAttribArray
#define glDisablei                                    glgenDisablei
#define glDispatchCompute                             glgenDispatchCompute
#define glDispatchComputeGroupSizeARB                 glgenDispatchComputeGroupSizeARB
#define glDispatchComputeIndirect                     glgenDispatchComputeIndirect
#define glDrawArrays                                  glgenDrawArrays
#define glDrawArraysIndirect                          glgenDrawArraysIndirect
#define glDrawArraysInstanced                         glgenDrawArraysInstanced
#define glDrawArraysInstancedARB                      glgenDrawArraysInstancedARB
#define glDrawArraysInstancedBaseInstance             glgenDrawArraysInstancedBaseInstance
#define glDrawArraysInstancedEXT                      glgenDrawArraysInstancedEXT
#define glDrawBuffer                                  glgenDrawBuffer
#define glDrawBuffers                                 glgenDrawBuffers
#define glDrawCommandsAddressNV                       glgenDrawCommandsAddressNV
#define glDrawCommandsNV                              glgenDrawCommandsNV
#define glDrawCommandsStatesAddressNV                 glgenDrawCommandsStatesAddressNV
#define glDrawCommandsStatesNV                        glgenDrawCommandsStatesNV
#define glDrawElements                                glgenDrawElements
#define glDrawElementsBaseVertex                      glgenDrawElementsBaseVertex
#define glDrawElementsIndirect                        glgenDrawElementsIndirect
#define glDrawElementsInstanced                       glgenDrawElementsInstanced
#define glDrawElementsInstancedARB                    glgenDrawElementsInstancedARB
#define glDrawElementsInstancedBaseInstance           glgenDrawElementsInstancedBaseInstance
#define glDrawElementsInstancedBaseVertex             glgenDrawElementsInstancedBaseVertex
#define glDrawElementsInstancedBaseVertexBaseInstance glgenDrawElementsInstancedBaseVertexBaseInstance
#define glDrawElementsInstancedEXT                    glgenDrawElementsInstancedEXT
#define glDrawMeshTasksIndirectNV                     glgenDrawMeshTasksIndirectNV
#define glDrawMeshTasksNV                             glgenDrawMeshTasksNV
#define glDrawRangeElements                           glgenDrawRangeElements
#define glDrawRangeElementsBaseVertex                 glgenDrawRangeElementsBaseVertex
#define glDrawTransformFeedback                       glgenDrawTransformFeedback
#define glDrawTransformFeedbackInstanced              glgenDrawTransformFeedbackInstanced
#define glDrawTransformFeedbackStream                 glgenDrawTransformFeedbackStream
#define glDrawTransformFeedbackStreamInstanced        glgenDrawTransformFeedbackStreamInstanced
#define glDrawVkImageNV                               glgenDrawVkImageNV
#define glEGLImageTargetTexStorageEXT                 glgenEGLImageTargetTexStorageEXT
#define glEGLImageTargetTextureStorageEXT             glgenEGLImageTargetTextureStorageEXT
#define glEdgeFlagFormatNV                            glgenEdgeFlagFormatNV
#define glEnable                                      glgenEnable
#define glEnableClientStateIndexedEXT                 glgenEnableClientStateIndexedEXT
#define glEnableClientStateiEXT                       glgenEnableClientStateiEXT
#define glEnableIndexedEXT                            glgenEnableIndexedEXT
#define glEnableVertexArrayAttrib                     glgenEnableVertexArrayAttrib
#define glEnableVertexArrayAttribEXT                  glgenEnableVertexArrayAttribEXT
#define glEnableVertexArrayEXT                        glgenEnableVertexArrayEXT
#define glEnableVertexAttribArray                     glgenEnableVertexAttribArray
#define glEnablei                                     glgenEnablei
#define glEndConditionalRender                        glgenEndConditionalRender
#define glEndConditionalRenderNV                      glgenEndConditionalRenderNV
#define glEndPerfMonitorAMD                           glgenEndPerfMonitorAMD
#define glEndPerfQueryINTEL                           glgenEndPerfQueryINTEL
#define glEndQuery                                    glgenEndQuery
#define glEndQueryIndexed                             glgenEndQueryIndexed
#define glEndTransformFeedback                        glgenEndTransformFeedback
#define glEvaluateDepthValuesARB                      glgenEvaluateDepthValuesARB
#define glFenceSync                                   glgenFenceSync
#define glFinish                                      glgenFinish
#define glFlush                                       glgenFlush
#define glFlushMappedBufferRange                      glgenFlushMappedBufferRange
#define glFlushMappedNamedBufferRange                 glgenFlushMappedNamedBufferRange
#define glFlushMappedNamedBufferRangeEXT              glgenFlushMappedNamedBufferRangeEXT
#define glFogCoordFormatNV                            glgenFogCoordFormatNV
#define glFragmentCoverageColorNV                     glgenFragmentCoverageColorNV
#define glFramebufferDrawBufferEXT                    glgenFramebufferDrawBufferEXT
#define glFramebufferDrawBuffersEXT                   glgenFramebufferDrawBuffersEXT
#define glFramebufferFetchBarrierEXT                  glgenFramebufferFetchBarrierEXT
#define glFramebufferParameteri                       glgenFramebufferParameteri
#define glFramebufferParameteriMESA                   glgenFramebufferParameteriMESA
#define glFramebufferReadBufferEXT                    glgenFramebufferReadBufferEXT
#define glFramebufferRenderbuffer                     glgenFramebufferRenderbuffer
#define glFramebufferSampleLocationsfvARB             glgenFramebufferSampleLocationsfvARB
#define glFramebufferSampleLocationsfvNV              glgenFramebufferSampleLocationsfvNV
#define glFramebufferTexture                          glgenFramebufferTexture
#define glFramebufferTexture1D                        glgenFramebufferTexture1D
#define glFramebufferTexture2D                        glgenFramebufferTexture2D
#define glFramebufferTexture3D                        glgenFramebufferTexture3D
#define glFramebufferTextureARB                       glgenFramebufferTextureARB
#define glFramebufferTextureFaceARB                   glgenFramebufferTextureFaceARB
#define glFramebufferTextureLayer                     glgenFramebufferTextureLayer
#define glFramebufferTextureLayerARB                  glgenFramebufferTextureLayerARB
#define glFramebufferTextureMultiviewOVR              glgenFramebufferTextureMultiviewOVR
#define glFrontFace                                   glgenFrontFace
#define glGenBuffers                                  glgenGenBuffers
#define glGenFramebuffers                             glgenGenFramebuffers
#define glGenPathsNV                                  glgenGenPathsNV
#define glGenPerfMonitorsAMD                          glgenGenPerfMonitorsAMD
#define glGenProgramPipelines                         glgenGenProgramPipelines
#define glGenQueries                                  glgenGenQueries
#define glGenRenderbuffers                            glgenGenRenderbuffers
#define glGenSamplers                                 glgenGenSamplers
#define glGenTextures                                 glgenGenTextures
#define glGenTransformFeedbacks                       glgenGenTransformFeedbacks
#define glGenVertexArrays                             glgenGenVertexArrays
#define glGenerateMipmap                              glgenGenerateMipmap
#define glGenerateMultiTexMipmapEXT                   glgenGenerateMultiTexMipmapEXT
#define glGenerateTextureMipmap                       glgenGenerateTextureMipmap
#define glGenerateTextureMipmapEXT                    glgenGenerateTextureMipmapEXT
#define glGetActiveAtomicCounterBufferiv              glgenGetActiveAtomicCounterBufferiv
#define glGetActiveAttrib                             glgenGetActiveAttrib
#define glGetActiveSubroutineName                     glgenGetActiveSubroutineName
#define glGetActiveSubroutineUniformName              glgenGetActiveSubroutineUniformName
#define glGetActiveSubroutineUniformiv                glgenGetActiveSubroutineUniformiv
#define glGetActiveUniform                            glgenGetActiveUniform
#define glGetActiveUniformBlockName                   glgenGetActiveUniformBlockName
#define glGetActiveUniformBlockiv                     glgenGetActiveUniformBlockiv
#define glGetActiveUniformName                        glgenGetActiveUniformName
#define glGetActiveUniformsiv                         glgenGetActiveUniformsiv
#define glGetAttachedShaders                          glgenGetAttachedShaders
#define glGetAttribLocation                           glgenGetAttribLocation
#define glGetBooleanIndexedvEXT                       glgenGetBooleanIndexedvEXT
#define glGetBooleani_v                               glgenGetBooleani_v
#define glGetBooleanv                                 glgenGetBooleanv
#define glGetBufferParameteri64v                      glgenGetBufferParameteri64v
#define glGetBufferParameteriv                        glgenGetBufferParameteriv
#define glGetBufferParameterui64vNV                   glgenGetBufferParameterui64vNV
#define glGetBufferPointerv                           glgenGetBufferPointerv
#define glGetBufferSubData                            glgenGetBufferSubData
#define glGetCommandHeaderNV                          glgenGetCommandHeaderNV
#define glGetCompressedMultiTexImageEXT               glgenGetCompressedMultiTexImageEXT
#define glGetCompressedTexImage                       glgenGetCompressedTexImage
#define glGetCompressedTextureImage                   glgenGetCompressedTextureImage
#define glGetCompressedTextureImageEXT                glgenGetCompressedTextureImageEXT
#define glGetCompressedTextureSubImage                glgenGetCompressedTextureSubImage
#define glGetCoverageModulationTableNV                glgenGetCoverageModulationTableNV
#define glGetDebugMessageLog                          glgenGetDebugMessageLog
#define glGetDebugMessageLogARB                       glgenGetDebugMessageLogARB
#define glGetDoubleIndexedvEXT                        glgenGetDoubleIndexedvEXT
#define glGetDoublei_v                                glgenGetDoublei_v
#define glGetDoublei_vEXT                             glgenGetDoublei_vEXT
#define glGetDoublev                                  glgenGetDoublev
#define glGetError                                    glgenGetError
#define glGetFirstPerfQueryIdINTEL                    glgenGetFirstPerfQueryIdINTEL
#define glGetFloatIndexedvEXT                         glgenGetFloatIndexedvEXT
#define glGetFloati_v                                 glgenGetFloati_v
#define glGetFloati_vEXT                              glgenGetFloati_vEXT
#define glGetFloatv                                   glgenGetFloatv
#define glGetFragDataIndex                            glgenGetFragDataIndex
#define glGetFragDataLocation                         glgenGetFragDataLocation
#define glGetFramebufferAttachmentParameteriv         glgenGetFramebufferAttachmentParameteriv
#define glGetFramebufferParameteriv                   glgenGetFramebufferParameteriv
#define glGetFramebufferParameterivEXT                glgenGetFramebufferParameterivEXT
#define glGetFramebufferParameterivMESA               glgenGetFramebufferParameterivMESA
#define glGetGraphicsResetStatus                      glgenGetGraphicsResetStatus
#define glGetGraphicsResetStatusARB                   glgenGetGraphicsResetStatusARB
#define glGetImageHandleARB                           glgenGetImageHandleARB
#define glGetImageHandleNV                            glgenGetImageHandleNV
#define glGetInteger64i_v                             glgenGetInteger64i_v
#define glGetInteger64v                               glgenGetInteger64v
#define glGetIntegerIndexedvEXT                       glgenGetIntegerIndexedvEXT
#define glGetIntegeri_v                               glgenGetIntegeri_v
#define glGetIntegerui64i_vNV                         glgenGetIntegerui64i_vNV
#define glGetIntegerui64vNV                           glgenGetIntegerui64vNV
#define glGetIntegerv                                 glgenGetIntegerv
#define glGetInternalformatSampleivNV                 glgenGetInternalformatSampleivNV
#define glGetInternalformati64v                       glgenGetInternalformati64v
#define glGetInternalformativ                         glgenGetInternalformativ
#define glGetMemoryObjectDetachedResourcesuivNV       glgenGetMemoryObjectDetachedResourcesuivNV
#define glGetMultiTexEnvfvEXT                         glgenGetMultiTexEnvfvEXT
#define glGetMultiTexEnvivEXT                         glgenGetMultiTexEnvivEXT
#define glGetMultiTexGendvEXT                         glgenGetMultiTexGendvEXT
#define glGetMultiTexGenfvEXT                         glgenGetMultiTexGenfvEXT
#define glGetMultiTexGenivEXT                         glgenGetMultiTexGenivEXT
#define glGetMultiTexImageEXT                         glgenGetMultiTexImageEXT
#define glGetMultiTexLevelParameterfvEXT              glgenGetMultiTexLevelParameterfvEXT
#define glGetMultiTexLevelParameterivEXT              glgenGetMultiTexLevelParameterivEXT
#define glGetMultiTexParameterIivEXT                  glgenGetMultiTexParameterIivEXT
#define glGetMultiTexParameterIuivEXT                 glgenGetMultiTexParameterIuivEXT
#define glGetMultiTexParameterfvEXT                   glgenGetMultiTexParameterfvEXT
#define glGetMultiTexParameterivEXT                   glgenGetMultiTexParameterivEXT
#define glGetMultisamplefv                            glgenGetMultisamplefv
#define glGetNamedBufferParameteri64v                 glgenGetNamedBufferParameteri64v
#define glGetNamedBufferParameteriv                   glgenGetNamedBufferParameteriv
#define glGetNamedBufferParameterivEXT                glgenGetNamedBufferParameterivEXT
#define glGetNamedBufferParameterui64vNV              glgenGetNamedBufferParameterui64vNV
#define glGetNamedBufferPointerv                      glgenGetNamedBufferPointerv
#define glGetNamedBufferPointervEXT                   glgenGetNamedBufferPointervEXT
#define glGetNamedBufferSubData                       glgenGetNamedBufferSubData
#define glGetNamedBufferSubDataEXT                    glgenGetNamedBufferSubDataEXT
#define glGetNamedFramebufferAttachmentParameteriv    glgenGetNamedFramebufferAttachmentParameteriv
#define glGetNamedFramebufferAttachmentParameterivEXT glgenGetNamedFramebufferAttachmentParameterivEXT
#define glGetNamedFramebufferParameteriv              glgenGetNamedFramebufferParameteriv
#define glGetNamedFramebufferParameterivEXT           glgenGetNamedFramebufferParameterivEXT
#define glGetNamedProgramLocalParameterIivEXT         glgenGetNamedProgramLocalParameterIivEXT
#define glGetNamedProgramLocalParameterIuivEXT        glgenGetNamedProgramLocalParameterIuivEXT
#define glGetNamedProgramLocalParameterdvEXT          glgenGetNamedProgramLocalParameterdvEXT
#define glGetNamedProgramLocalParameterfvEXT          glgenGetNamedProgramLocalParameterfvEXT
#define glGetNamedProgramStringEXT                    glgenGetNamedProgramStringEXT
#define glGetNamedProgramivEXT                        glgenGetNamedProgramivEXT
#define glGetNamedRenderbufferParameteriv             glgenGetNamedRenderbufferParameteriv
#define glGetNamedRenderbufferParameterivEXT          glgenGetNamedRenderbufferParameterivEXT
#define glGetNamedStringARB                           glgenGetNamedStringARB
#define glGetNamedStringivARB                         glgenGetNamedStringivARB
#define glGetNextPerfQueryIdINTEL                     glgenGetNextPerfQueryIdINTEL
#define glGetObjectLabel                              glgenGetObjectLabel
#define glGetObjectLabelEXT                           glgenGetObjectLabelEXT
#define glGetObjectPtrLabel                           glgenGetObjectPtrLabel
#define glGetPathCommandsNV                           glgenGetPathCommandsNV
#define glGetPathCoordsNV                             glgenGetPathCoordsNV
#define glGetPathDashArrayNV                          glgenGetPathDashArrayNV
#define glGetPathLengthNV                             glgenGetPathLengthNV
#define glGetPathMetricRangeNV                        glgenGetPathMetricRangeNV
#define glGetPathMetricsNV                            glgenGetPathMetricsNV
#define glGetPathParameterfvNV                        glgenGetPathParameterfvNV
#define glGetPathParameterivNV                        glgenGetPathParameterivNV
#define glGetPathSpacingNV                            glgenGetPathSpacingNV
#define glGetPerfCounterInfoINTEL                     glgenGetPerfCounterInfoINTEL
#define glGetPerfMonitorCounterDataAMD                glgenGetPerfMonitorCounterDataAMD
#define glGetPerfMonitorCounterInfoAMD                glgenGetPerfMonitorCounterInfoAMD
#define glGetPerfMonitorCounterStringAMD              glgenGetPerfMonitorCounterStringAMD
#define glGetPerfMonitorCountersAMD                   glgenGetPerfMonitorCountersAMD
#define glGetPerfMonitorGroupStringAMD                glgenGetPerfMonitorGroupStringAMD
#define glGetPerfMonitorGroupsAMD                     glgenGetPerfMonitorGroupsAMD
#define glGetPerfQueryDataINTEL                       glgenGetPerfQueryDataINTEL
#define glGetPerfQueryIdByNameINTEL                   glgenGetPerfQueryIdByNameINTEL
#define glGetPerfQueryInfoINTEL                       glgenGetPerfQueryInfoINTEL
#define glGetPointerIndexedvEXT                       glgenGetPointerIndexedvEXT
#define glGetPointeri_vEXT                            glgenGetPointeri_vEXT
#define glGetPointerv                                 glgenGetPointerv
#define glGetProgramBinary                            glgenGetProgramBinary
#define glGetProgramInfoLog                           glgenGetProgramInfoLog
#define glGetProgramInterfaceiv                       glgenGetProgramInterfaceiv
#define glGetProgramPipelineInfoLog                   glgenGetProgramPipelineInfoLog
#define glGetProgramPipelineiv                        glgenGetProgramPipelineiv
#define glGetProgramResourceIndex                     glgenGetProgramResourceIndex
#define glGetProgramResourceLocation                  glgenGetProgramResourceLocation
#define glGetProgramResourceLocationIndex             glgenGetProgramResourceLocationIndex
#define glGetProgramResourceName                      glgenGetProgramResourceName
#define glGetProgramResourcefvNV                      glgenGetProgramResourcefvNV
#define glGetProgramResourceiv                        glgenGetProgramResourceiv
#define glGetProgramStageiv                           glgenGetProgramStageiv
#define glGetProgramiv                                glgenGetProgramiv
#define glGetQueryBufferObjecti64v                    glgenGetQueryBufferObjecti64v
#define glGetQueryBufferObjectiv                      glgenGetQueryBufferObjectiv
#define glGetQueryBufferObjectui64v                   glgenGetQueryBufferObjectui64v
#define glGetQueryBufferObjectuiv                     glgenGetQueryBufferObjectuiv
#define glGetQueryIndexediv                           glgenGetQueryIndexediv
#define glGetQueryObjecti64v                          glgenGetQueryObjecti64v
#define glGetQueryObjectiv                            glgenGetQueryObjectiv
#define glGetQueryObjectui64v                         glgenGetQueryObjectui64v
#define glGetQueryObjectuiv                           glgenGetQueryObjectuiv
#define glGetQueryiv                                  glgenGetQueryiv
#define glGetRenderbufferParameteriv                  glgenGetRenderbufferParameteriv
#define glGetSamplerParameterIiv                      glgenGetSamplerParameterIiv
#define glGetSamplerParameterIuiv                     glgenGetSamplerParameterIuiv
#define glGetSamplerParameterfv                       glgenGetSamplerParameterfv
#define glGetSamplerParameteriv                       glgenGetSamplerParameteriv
#define glGetShaderInfoLog                            glgenGetShaderInfoLog
#define glGetShaderPrecisionFormat                    glgenGetShaderPrecisionFormat
#define glGetShaderSource                             glgenGetShaderSource
#define glGetShaderiv                                 glgenGetShaderiv
#define glGetShadingRateImagePaletteNV                glgenGetShadingRateImagePaletteNV
#define glGetShadingRateSampleLocationivNV            glgenGetShadingRateSampleLocationivNV
#define glGetStageIndexNV                             glgenGetStageIndexNV
#define glGetString                                   glgenGetString
#define glGetStringi                                  glgenGetStringi
#define glGetSubroutineIndex                          glgenGetSubroutineIndex
#define glGetSubroutineUniformLocation                glgenGetSubroutineUniformLocation
#define glGetSynciv                                   glgenGetSynciv
#define glGetTexImage                                 glgenGetTexImage
#define glGetTexLevelParameterfv                      glgenGetTexLevelParameterfv
#define glGetTexLevelParameteriv                      glgenGetTexLevelParameteriv
#define glGetTexParameterIiv                          glgenGetTexParameterIiv
#define glGetTexParameterIuiv                         glgenGetTexParameterIuiv
#define glGetTexParameterfv                           glgenGetTexParameterfv
#define glGetTexParameteriv                           glgenGetTexParameteriv
#define glGetTextureHandleARB                         glgenGetTextureHandleARB
#define glGetTextureHandleNV                          glgenGetTextureHandleNV
#define glGetTextureImage                             glgenGetTextureImage
#define glGetTextureImageEXT                          glgenGetTextureImageEXT
#define glGetTextureLevelParameterfv                  glgenGetTextureLevelParameterfv
#define glGetTextureLevelParameterfvEXT               glgenGetTextureLevelParameterfvEXT
#define glGetTextureLevelParameteriv                  glgenGetTextureLevelParameteriv
#define glGetTextureLevelParameterivEXT               glgenGetTextureLevelParameterivEXT
#define glGetTextureParameterIiv                      glgenGetTextureParameterIiv
#define glGetTextureParameterIivEXT                   glgenGetTextureParameterIivEXT
#define glGetTextureParameterIuiv                     glgenGetTextureParameterIuiv
#define glGetTextureParameterIuivEXT                  glgenGetTextureParameterIuivEXT
#define glGetTextureParameterfv                       glgenGetTextureParameterfv
#define glGetTextureParameterfvEXT                    glgenGetTextureParameterfvEXT
#define glGetTextureParameteriv                       glgenGetTextureParameteriv
#define glGetTextureParameterivEXT                    glgenGetTextureParameterivEXT
#define glGetTextureSamplerHandleARB                  glgenGetTextureSamplerHandleARB
#define glGetTextureSamplerHandleNV                   glgenGetTextureSamplerHandleNV
#define glGetTextureSubImage                          glgenGetTextureSubImage
#define glGetTransformFeedbackVarying                 glgenGetTransformFeedbackVarying
#define glGetTransformFeedbacki64_v                   glgenGetTransformFeedbacki64_v
#define glGetTransformFeedbacki_v                     glgenGetTransformFeedbacki_v
#define glGetTransformFeedbackiv                      glgenGetTransformFeedbackiv
#define glGetUniformBlockIndex                        glgenGetUniformBlockIndex
#define glGetUniformIndices                           glgenGetUniformIndices
#define glGetUniformLocation                          glgenGetUniformLocation
#define glGetUniformSubroutineuiv                     glgenGetUniformSubroutineuiv
#define glGetUniformdv                                glgenGetUniformdv
#define glGetUniformfv                                glgenGetUniformfv
#define glGetUniformi64vARB                           glgenGetUniformi64vARB
#define glGetUniformi64vNV                            glgenGetUniformi64vNV
#define glGetUniformiv                                glgenGetUniformiv
#define glGetUniformui64vARB                          glgenGetUniformui64vARB
#define glGetUniformui64vNV                           glgenGetUniformui64vNV
#define glGetUniformuiv                               glgenGetUniformuiv
#define glGetVertexArrayIndexed64iv                   glgenGetVertexArrayIndexed64iv
#define glGetVertexArrayIndexediv                     glgenGetVertexArrayIndexediv
#define glGetVertexArrayIntegeri_vEXT                 glgenGetVertexArrayIntegeri_vEXT
#define glGetVertexArrayIntegervEXT                   glgenGetVertexArrayIntegervEXT
#define glGetVertexArrayPointeri_vEXT                 glgenGetVertexArrayPointeri_vEXT
#define glGetVertexArrayPointervEXT                   glgenGetVertexArrayPointervEXT
#define glGetVertexArrayiv                            glgenGetVertexArrayiv
#define glGetVertexAttribIiv                          glgenGetVertexAttribIiv
#define glGetVertexAttribIuiv                         glgenGetVertexAttribIuiv
#define glGetVertexAttribLdv                          glgenGetVertexAttribLdv
#define glGetVertexAttribLi64vNV                      glgenGetVertexAttribLi64vNV
#define glGetVertexAttribLui64vARB                    glgenGetVertexAttribLui64vARB
#define glGetVertexAttribLui64vNV                     glgenGetVertexAttribLui64vNV
#define glGetVertexAttribPointerv                     glgenGetVertexAttribPointerv
#define glGetVertexAttribdv                           glgenGetVertexAttribdv
#define glGetVertexAttribfv                           glgenGetVertexAttribfv
#define glGetVertexAttribiv                           glgenGetVertexAttribiv
#define glGetVkProcAddrNV                             glgenGetVkProcAddrNV
#define glGetnCompressedTexImage                      glgenGetnCompressedTexImage
#define glGetnCompressedTexImageARB                   glgenGetnCompressedTexImageARB
#define glGetnTexImage                                glgenGetnTexImage
#define glGetnTexImageARB                             glgenGetnTexImageARB
#define glGetnUniformdv                               glgenGetnUniformdv
#define glGetnUniformdvARB                            glgenGetnUniformdvARB
#define glGetnUniformfv                               glgenGetnUniformfv
#define glGetnUniformfvARB                            glgenGetnUniformfvARB
#define glGetnUniformi64vARB                          glgenGetnUniformi64vARB
#define glGetnUniformiv                               glgenGetnUniformiv
#define glGetnUniformivARB                            glgenGetnUniformivARB
#define glGetnUniformui64vARB                         glgenGetnUniformui64vARB
#define glGetnUniformuiv                              glgenGetnUniformuiv
#define glGetnUniformuivARB                           glgenGetnUniformuivARB
#define glHint                                        glgenHint
#define glIndexFormatNV                               glgenIndexFormatNV
#define glInsertEventMarkerEXT                        glgenInsertEventMarkerEXT
#define glInterpolatePathsNV                          glgenInterpolatePathsNV
#define glInvalidateBufferData                        glgenInvalidateBufferData
#define glInvalidateBufferSubData                     glgenInvalidateBufferSubData
#define glInvalidateFramebuffer                       glgenInvalidateFramebuffer
#define glInvalidateNamedFramebufferData              glgenInvalidateNamedFramebufferData
#define glInvalidateNamedFramebufferSubData           glgenInvalidateNamedFramebufferSubData
#define glInvalidateSubFramebuffer                    glgenInvalidateSubFramebuffer
#define glInvalidateTexImage                          glgenInvalidateTexImage
#define glInvalidateTexSubImage                       glgenInvalidateTexSubImage
#define glIsBuffer                                    glgenIsBuffer
#define glIsBufferResidentNV                          glgenIsBufferResidentNV
#define glIsCommandListNV                             glgenIsCommandListNV
#define glIsEnabled                                   glgenIsEnabled
#define glIsEnabledIndexedEXT                         glgenIsEnabledIndexedEXT
#define glIsEnabledi                                  glgenIsEnabledi
#define glIsFramebuffer                               glgenIsFramebuffer
#define glIsImageHandleResidentARB                    glgenIsImageHandleResidentARB
#define glIsImageHandleResidentNV                     glgenIsImageHandleResidentNV
#define glIsNamedBufferResidentNV                     glgenIsNamedBufferResidentNV
#define glIsNamedStringARB                            glgenIsNamedStringARB
#define glIsPathNV                                    glgenIsPathNV
#define glIsPointInFillPathNV                         glgenIsPointInFillPathNV
#define glIsPointInStrokePathNV                       glgenIsPointInStrokePathNV
#define glIsProgram                                   glgenIsProgram
#define glIsProgramPipeline                           glgenIsProgramPipeline
#define glIsQuery                                     glgenIsQuery
#define glIsRenderbuffer                              glgenIsRenderbuffer
#define glIsSampler                                   glgenIsSampler
#define glIsShader                                    glgenIsShader
#define glIsStateNV                                   glgenIsStateNV
#define glIsSync                                      glgenIsSync
#define glIsTexture                                   glgenIsTexture
#define glIsTextureHandleResidentARB                  glgenIsTextureHandleResidentARB
#define glIsTextureHandleResidentNV                   glgenIsTextureHandleResidentNV
#define glIsTransformFeedback                         glgenIsTransformFeedback
#define glIsVertexArray                               glgenIsVertexArray
#define glLabelObjectEXT                              glgenLabelObjectEXT
#define glLineWidth                                   glgenLineWidth
#define glLinkProgram                                 glgenLinkProgram
#define glListDrawCommandsStatesClientNV              glgenListDrawCommandsStatesClientNV
#define glLogicOp                                     glgenLogicOp
#define glMakeBufferNonResidentNV                     glgenMakeBufferNonResidentNV
#define glMakeBufferResidentNV                        glgenMakeBufferResidentNV
#define glMakeImageHandleNonResidentARB               glgenMakeImageHandleNonResidentARB
#define glMakeImageHandleNonResidentNV                glgenMakeImageHandleNonResidentNV
#define glMakeImageHandleResidentARB                  glgenMakeImageHandleResidentARB
#define glMakeImageHandleResidentNV                   glgenMakeImageHandleResidentNV
#define glMakeNamedBufferNonResidentNV                glgenMakeNamedBufferNonResidentNV
#define glMakeNamedBufferResidentNV                   glgenMakeNamedBufferResidentNV
#define glMakeTextureHandleNonResidentARB             glgenMakeTextureHandleNonResidentARB
#define glMakeTextureHandleNonResidentNV              glgenMakeTextureHandleNonResidentNV
#define glMakeTextureHandleResidentARB                glgenMakeTextureHandleResidentARB
#define glMakeTextureHandleResidentNV                 glgenMakeTextureHandleResidentNV
#define glMapBuffer                                   glgenMapBuffer
#define glMapBufferRange                              glgenMapBufferRange
#define glMapNamedBuffer                              glgenMapNamedBuffer
#define glMapNamedBufferEXT                           glgenMapNamedBufferEXT
#define glMapNamedBufferRange                         glgenMapNamedBufferRange
#define glMapNamedBufferRangeEXT                      glgenMapNamedBufferRangeEXT
#define glMatrixFrustumEXT                            glgenMatrixFrustumEXT
#define glMatrixLoad3x2fNV                            glgenMatrixLoad3x2fNV
#define glMatrixLoad3x3fNV                            glgenMatrixLoad3x3fNV
#define glMatrixLoadIdentityEXT                       glgenMatrixLoadIdentityEXT
#define glMatrixLoadTranspose3x3fNV                   glgenMatrixLoadTranspose3x3fNV
#define glMatrixLoadTransposedEXT                     glgenMatrixLoadTransposedEXT
#define glMatrixLoadTransposefEXT                     glgenMatrixLoadTransposefEXT
#define glMatrixLoaddEXT                              glgenMatrixLoaddEXT
#define glMatrixLoadfEXT                              glgenMatrixLoadfEXT
#define glMatrixMult3x2fNV                            glgenMatrixMult3x2fNV
#define glMatrixMult3x3fNV                            glgenMatrixMult3x3fNV
#define glMatrixMultTranspose3x3fNV                   glgenMatrixMultTranspose3x3fNV
#define glMatrixMultTransposedEXT                     glgenMatrixMultTransposedEXT
#define glMatrixMultTransposefEXT                     glgenMatrixMultTransposefEXT
#define glMatrixMultdEXT                              glgenMatrixMultdEXT
#define glMatrixMultfEXT                              glgenMatrixMultfEXT
#define glMatrixOrthoEXT                              glgenMatrixOrthoEXT
#define glMatrixPopEXT                                glgenMatrixPopEXT
#define glMatrixPushEXT                               glgenMatrixPushEXT
#define glMatrixRotatedEXT                            glgenMatrixRotatedEXT
#define glMatrixRotatefEXT                            glgenMatrixRotatefEXT
#define glMatrixScaledEXT                             glgenMatrixScaledEXT
#define glMatrixScalefEXT                             glgenMatrixScalefEXT
#define glMatrixTranslatedEXT                         glgenMatrixTranslatedEXT
#define glMatrixTranslatefEXT                         glgenMatrixTranslatefEXT
#define glMaxShaderCompilerThreadsARB                 glgenMaxShaderCompilerThreadsARB
#define glMaxShaderCompilerThreadsKHR                 glgenMaxShaderCompilerThreadsKHR
#define glMemoryBarrier                               glgenMemoryBarrier
#define glMemoryBarrierByRegion                       glgenMemoryBarrierByRegion
#define glMinSampleShading                            glgenMinSampleShading
#define glMinSampleShadingARB                         glgenMinSampleShadingARB
#define glMultiDrawArrays                             glgenMultiDrawArrays
#define glMultiDrawArraysIndirect                     glgenMultiDrawArraysIndirect
#define glMultiDrawArraysIndirectBindlessCountNV      glgenMultiDrawArraysIndirectBindlessCountNV
#define glMultiDrawArraysIndirectBindlessNV           glgenMultiDrawArraysIndirectBindlessNV
#define glMultiDrawArraysIndirectCount                glgenMultiDrawArraysIndirectCount
#define glMultiDrawArraysIndirectCountARB             glgenMultiDrawArraysIndirectCountARB
#define glMultiDrawElements                           glgenMultiDrawElements
#define glMultiDrawElementsBaseVertex                 glgenMultiDrawElementsBaseVertex
#define glMultiDrawElementsIndirect                   glgenMultiDrawElementsIndirect
#define glMultiDrawElementsIndirectBindlessCountNV    glgenMultiDrawElementsIndirectBindlessCountNV
#define glMultiDrawElementsIndirectBindlessNV         glgenMultiDrawElementsIndirectBindlessNV
#define glMultiDrawElementsIndirectCount              glgenMultiDrawElementsIndirectCount
#define glMultiDrawElementsIndirectCountARB           glgenMultiDrawElementsIndirectCountARB
#define glMultiDrawMeshTasksIndirectCountNV           glgenMultiDrawMeshTasksIndirectCountNV
#define glMultiDrawMeshTasksIndirectNV                glgenMultiDrawMeshTasksIndirectNV
#define glMultiTexBufferEXT                           glgenMultiTexBufferEXT
#define glMultiTexCoordPointerEXT                     glgenMultiTexCoordPointerEXT
#define glMultiTexEnvfEXT                             glgenMultiTexEnvfEXT
#define glMultiTexEnvfvEXT                            glgenMultiTexEnvfvEXT
#define glMultiTexEnviEXT                             glgenMultiTexEnviEXT
#define glMultiTexEnvivEXT                            glgenMultiTexEnvivEXT
#define glMultiTexGendEXT                             glgenMultiTexGendEXT
#define glMultiTexGendvEXT                            glgenMultiTexGendvEXT
#define glMultiTexGenfEXT                             glgenMultiTexGenfEXT
#define glMultiTexGenfvEXT                            glgenMultiTexGenfvEXT
#define glMultiTexGeniEXT                             glgenMultiTexGeniEXT
#define glMultiTexGenivEXT                            glgenMultiTexGenivEXT
#define glMultiTexImage1DEXT                          glgenMultiTexImage1DEXT
#define glMultiTexImage2DEXT                          glgenMultiTexImage2DEXT
#define glMultiTexImage3DEXT                          glgenMultiTexImage3DEXT
#define glMultiTexParameterIivEXT                     glgenMultiTexParameterIivEXT
#define glMultiTexParameterIuivEXT                    glgenMultiTexParameterIuivEXT
#define glMultiTexParameterfEXT                       glgenMultiTexParameterfEXT
#define glMultiTexParameterfvEXT                      glgenMultiTexParameterfvEXT
#define glMultiTexParameteriEXT                       glgenMultiTexParameteriEXT
#define glMultiTexParameterivEXT                      glgenMultiTexParameterivEXT
#define glMultiTexRenderbufferEXT                     glgenMultiTexRenderbufferEXT
#define glMultiTexSubImage1DEXT                       glgenMultiTexSubImage1DEXT
#define glMultiTexSubImage2DEXT                       glgenMultiTexSubImage2DEXT
#define glMultiTexSubImage3DEXT                       glgenMultiTexSubImage3DEXT
#define glNamedBufferAttachMemoryNV                   glgenNamedBufferAttachMemoryNV
#define glNamedBufferData                             glgenNamedBufferData
#define glNamedBufferDataEXT                          glgenNamedBufferDataEXT
#define glNamedBufferPageCommitmentARB                glgenNamedBufferPageCommitmentARB
#define glNamedBufferPageCommitmentEXT                glgenNamedBufferPageCommitmentEXT
#define glNamedBufferStorage                          glgenNamedBufferStorage
#define glNamedBufferStorageEXT                       glgenNamedBufferStorageEXT
#define glNamedBufferSubData                          glgenNamedBufferSubData
#define glNamedBufferSubDataEXT                       glgenNamedBufferSubDataEXT
#define glNamedCopyBufferSubDataEXT                   glgenNamedCopyBufferSubDataEXT
#define glNamedFramebufferDrawBuffer                  glgenNamedFramebufferDrawBuffer
#define glNamedFramebufferDrawBuffers                 glgenNamedFramebufferDrawBuffers
#define glNamedFramebufferParameteri                  glgenNamedFramebufferParameteri
#define glNamedFramebufferParameteriEXT               glgenNamedFramebufferParameteriEXT
#define glNamedFramebufferReadBuffer                  glgenNamedFramebufferReadBuffer
#define glNamedFramebufferRenderbuffer                glgenNamedFramebufferRenderbuffer
#define glNamedFramebufferRenderbufferEXT             glgenNamedFramebufferRenderbufferEXT
#define glNamedFramebufferSampleLocationsfvARB        glgenNamedFramebufferSampleLocationsfvARB
#define glNamedFramebufferSampleLocationsfvNV         glgenNamedFramebufferSampleLocationsfvNV
#define glNamedFramebufferTexture                     glgenNamedFramebufferTexture
#define glNamedFramebufferTexture1DEXT                glgenNamedFramebufferTexture1DEXT
#define glNamedFramebufferTexture2DEXT                glgenNamedFramebufferTexture2DEXT
#define glNamedFramebufferTexture3DEXT                glgenNamedFramebufferTexture3DEXT
#define glNamedFramebufferTextureEXT                  glgenNamedFramebufferTextureEXT
#define glNamedFramebufferTextureFaceEXT              glgenNamedFramebufferTextureFaceEXT
#define glNamedFramebufferTextureLayer                glgenNamedFramebufferTextureLayer
#define glNamedFramebufferTextureLayerEXT             glgenNamedFramebufferTextureLayerEXT
#define glNamedProgramLocalParameter4dEXT             glgenNamedProgramLocalParameter4dEXT
#define glNamedProgramLocalParameter4dvEXT            glgenNamedProgramLocalParameter4dvEXT
#define glNamedProgramLocalParameter4fEXT             glgenNamedProgramLocalParameter4fEXT
#define glNamedProgramLocalParameter4fvEXT            glgenNamedProgramLocalParameter4fvEXT
#define glNamedProgramLocalParameterI4iEXT            glgenNamedProgramLocalParameterI4iEXT
#define glNamedProgramLocalParameterI4ivEXT           glgenNamedProgramLocalParameterI4ivEXT
#define glNamedProgramLocalParameterI4uiEXT           glgenNamedProgramLocalParameterI4uiEXT
#define glNamedProgramLocalParameterI4uivEXT          glgenNamedProgramLocalParameterI4uivEXT
#define glNamedProgramLocalParameters4fvEXT           glgenNamedProgramLocalParameters4fvEXT
#define glNamedProgramLocalParametersI4ivEXT          glgenNamedProgramLocalParametersI4ivEXT
#define glNamedProgramLocalParametersI4uivEXT         glgenNamedProgramLocalParametersI4uivEXT
#define glNamedProgramStringEXT                       glgenNamedProgramStringEXT
#define glNamedRenderbufferStorage                    glgenNamedRenderbufferStorage
#define glNamedRenderbufferStorageEXT                 glgenNamedRenderbufferStorageEXT
#define glNamedRenderbufferStorageMultisample         glgenNamedRenderbufferStorageMultisample
#define glNamedRenderbufferStorageMultisampleAdvancedAMD glgenNamedRenderbufferStorageMultisampleAdvancedAMD
#define glNamedRenderbufferStorageMultisampleCoverageEXT glgenNamedRenderbufferStorageMultisampleCoverageEXT
#define glNamedRenderbufferStorageMultisampleEXT      glgenNamedRenderbufferStorageMultisampleEXT
#define glNamedStringARB                              glgenNamedStringARB
#define glNormalFormatNV                              glgenNormalFormatNV
#define glObjectLabel                                 glgenObjectLabel
#define glObjectPtrLabel                              glgenObjectPtrLabel
#define glPatchParameterfv                            glgenPatchParameterfv
#define glPatchParameteri                             glgenPatchParameteri
#define glPathCommandsNV                              glgenPathCommandsNV
#define glPathCoordsNV                                glgenPathCoordsNV
#define glPathCoverDepthFuncNV                        glgenPathCoverDepthFuncNV
#define glPathDashArrayNV                             glgenPathDashArrayNV
#define glPathGlyphIndexArrayNV                       glgenPathGlyphIndexArrayNV
#define glPathGlyphIndexRangeNV                       glgenPathGlyphIndexRangeNV
#define glPathGlyphRangeNV                            glgenPathGlyphRangeNV
#define glPathGlyphsNV                                glgenPathGlyphsNV
#define glPathMemoryGlyphIndexArrayNV                 glgenPathMemoryGlyphIndexArrayNV
#define glPathParameterfNV                            glgenPathParameterfNV
#define glPathParameterfvNV                           glgenPathParameterfvNV
#define glPathParameteriNV                            glgenPathParameteriNV
#define glPathParameterivNV                           glgenPathParameterivNV
#define glPathStencilDepthOffsetNV                    glgenPathStencilDepthOffsetNV
#define glPathStencilFuncNV                           glgenPathStencilFuncNV
#define glPathStringNV                                glgenPathStringNV
#define glPathSubCommandsNV                           glgenPathSubCommandsNV
#define glPathSubCoordsNV                             glgenPathSubCoordsNV
#define glPauseTransformFeedback                      glgenPauseTransformFeedback
#define glPixelStoref                                 glgenPixelStoref
#define glPixelStorei                                 glgenPixelStorei
#define glPointAlongPathNV                            glgenPointAlongPathNV
#define glPointParameterf                             glgenPointParameterf
#define glPointParameterfv                            glgenPointParameterfv
#define glPointParameteri                             glgenPointParameteri
#define glPointParameteriv                            glgenPointParameteriv
#define glPointSize                                   glgenPointSize
#define glPolygonMode                                 glgenPolygonMode
#define glPolygonOffset                               glgenPolygonOffset
#define glPolygonOffsetClamp                          glgenPolygonOffsetClamp
#define glPolygonOffsetClampEXT                       glgenPolygonOffsetClampEXT
#define glPopDebugGroup                               glgenPopDebugGroup
#define glPopGroupMarkerEXT                           glgenPopGroupMarkerEXT
#define glPrimitiveBoundingBoxARB                     glgenPrimitiveBoundingBoxARB
#define glPrimitiveRestartIndex                       glgenPrimitiveRestartIndex
#define glProgramBinary                               glgenProgramBinary
#define glProgramParameteri                           glgenProgramParameteri
#define glProgramParameteriARB                        glgenProgramParameteriARB
#define glProgramPathFragmentInputGenNV               glgenProgramPathFragmentInputGenNV
#define glProgramUniform1d                            glgenProgramUniform1d
#define glProgramUniform1dEXT                         glgenProgramUniform1dEXT
#define glProgramUniform1dv                           glgenProgramUniform1dv
#define glProgramUniform1dvEXT                        glgenProgramUniform1dvEXT
#define glProgramUniform1f                            glgenProgramUniform1f
#define glProgramUniform1fEXT                         glgenProgramUniform1fEXT
#define glProgramUniform1fv                           glgenProgramUniform1fv
#define glProgramUniform1fvEXT                        glgenProgramUniform1fvEXT
#define glProgramUniform1i                            glgenProgramUniform1i
#define glProgramUniform1i64ARB                       glgenProgramUniform1i64ARB
#define glProgramUniform1i64NV                        glgenProgramUniform1i64NV
#define glProgramUniform1i64vARB                      glgenProgramUniform1i64vARB
#define glProgramUniform1i64vNV                       glgenProgramUniform1i64vNV
#define glProgramUniform1iEXT                         glgenProgramUniform1iEXT
#define glProgramUniform1iv                           glgenProgramUniform1iv
#define glProgramUniform1ivEXT                        glgenProgramUniform1ivEXT
#define glProgramUniform1ui                           glgenProgramUniform1ui
#define glProgramUniform1ui64ARB                      glgenProgramUniform1ui64ARB
#define glProgramUniform1ui64NV                       glgenProgramUniform1ui64NV
#define glProgramUniform1ui64vARB                     glgenProgramUniform1ui64vARB
#define glProgramUniform1ui64vNV                      glgenProgramUniform1ui64vNV
#define glProgramUniform1uiEXT                        glgenProgramUniform1uiEXT
#define glProgramUniform1uiv                          glgenProgramUniform1uiv
#define glProgramUniform1uivEXT                       glgenProgramUniform1uivEXT
#define glProgramUniform2d                            glgenProgramUniform2d
#define glProgramUniform2dEXT                         glgenProgramUniform2dEXT
#define glProgramUniform2dv                           glgenProgramUniform2dv
#define glProgramUniform2dvEXT                        glgenProgramUniform2dvEXT
#define glProgramUniform2f                            glgenProgramUniform2f
#define glProgramUniform2fEXT                         glgenProgramUniform2fEXT
#define glProgramUniform2fv                           glgenProgramUniform2fv
#define glProgramUniform2fvEXT                        glgenProgramUniform2fvEXT
#define glProgramUniform2i                            glgenProgramUniform2i
#define glProgramUniform2i64ARB                       glgenProgramUniform2i64ARB
#define glProgramUniform2i64NV                        glgenProgramUniform2i64NV
#define glProgramUniform2i64vARB                      glgenProgramUniform2i64vARB
#define glProgramUniform2i64vNV                       glgenProgramUniform2i64vNV
#define glProgramUniform2iEXT                         glgenProgramUniform2iEXT
#define glProgramUniform2iv                           glgenProgramUniform2iv
#define glProgramUniform2ivEXT                        glgenProgramUniform2ivEXT
#define glProgramUniform2ui                           glgenProgramUniform2ui
#define glProgramUniform2ui64ARB                      glgenProgramUniform2ui64ARB
#define glProgramUniform2ui64NV                       glgenProgramUniform2ui64NV
#define glProgramUniform2ui64vARB                     glgenProgramUniform2ui64vARB
#define glProgramUniform2ui64vNV                      glgenProgramUniform2ui64vNV
#define glProgramUniform2uiEXT                        glgenProgramUniform2uiEXT
#define glProgramUniform2uiv                          glgenProgramUniform2uiv
#define glProgramUniform2uivEXT                       glgenProgramUniform2uivEXT
#define glProgramUniform3d                            glgenProgramUniform3d
#define glProgramUniform3dEXT                         glgenProgramUniform3dEXT
#define glProgramUniform3dv                           glgenProgramUniform3dv
#define glProgramUniform3dvEXT                        glgenProgramUniform3dvEXT
#define glProgramUniform3f                            glgenProgramUniform3f
#define glProgramUniform3fEXT                         glgenProgramUniform3fEXT
#define glProgramUniform3fv                           glgenProgramUniform3fv
#define glProgramUniform3fvEXT                        glgenProgramUniform3fvEXT
#define glProgramUniform3i                            glgenProgramUniform3i
#define glProgramUniform3i64ARB                       glgenProgramUniform3i64ARB
#define glProgramUniform3i64NV                        glgenProgramUniform3i64NV
#define glProgramUniform3i64vARB                      glgenProgramUniform3i64vARB
#define glProgramUniform3i64vNV                       glgenProgramUniform3i64vNV
#define glProgramUniform3iEXT                         glgenProgramUniform3iEXT
#define glProgramUniform3iv                           glgenProgramUniform3iv
#define glProgramUniform3ivEXT                        glgenProgramUniform3ivEXT
#define glProgramUniform3ui                           glgenProgramUniform3ui
#define glProgramUniform3ui64ARB                      glgenProgramUniform3ui64ARB
#define glProgramUniform3ui64NV                       glgenProgramUniform3ui64NV
#define glProgramUniform3ui64vARB                     glgenProgramUniform3ui64vARB
#define glProgramUniform3ui64vNV                      glgenProgramUniform3ui64vNV
#define glProgramUniform3uiEXT                        glgenProgramUniform3uiEXT
#define glProgramUniform3uiv                          glgenProgramUniform3uiv
#define glProgramUniform3uivEXT                       glgenProgramUniform3uivEXT
#define glProgramUniform4d                            glgenProgramUniform4d
#define glProgramUniform4dEXT                         glgenProgramUniform4dEXT
#define glProgramUniform4dv                           glgenProgramUniform4dv
#define glProgramUniform4dvEXT                        glgenProgramUniform4dvEXT
#define glProgramUniform4f                            glgenProgramUniform4f
#define glProgramUniform4fEXT                         glgenProgramUniform4fEXT
#define glProgramUniform4fv                           glgenProgramUniform4fv
#define glProgramUniform4fvEXT                        glgenProgramUniform4fvEXT
#define glProgramUniform4i                            glgenProgramUniform4i
#define glProgramUniform4i64ARB                       glgenProgramUniform4i64ARB
#define glProgramUniform4i64NV                        glgenProgramUniform4i64NV
#define glProgramUniform4i64vARB                      glgenProgramUniform4i64vARB
#define glProgramUniform4i64vNV                       glgenProgramUniform4i64vNV
#define glProgramUniform4iEXT                         glgenProgramUniform4iEXT
#define glProgramUniform4iv                           glgenProgramUniform4iv
#define glProgramUniform4ivEXT                        glgenProgramUniform4ivEXT
#define glProgramUniform4ui                           glgenProgramUniform4ui
#define glProgramUniform4ui64ARB                      glgenProgramUniform4ui64ARB
#define glProgramUniform4ui64NV                       glgenProgramUniform4ui64NV
#define glProgramUniform4ui64vARB                     glgenProgramUniform4ui64vARB
#define glProgramUniform4ui64vNV                      glgenProgramUniform4ui64vNV
#define glProgramUniform4uiEXT                        glgenProgramUniform4uiEXT
#define glProgramUniform4uiv                          glgenProgramUniform4uiv
#define glProgramUniform4uivEXT                       glgenProgramUniform4uivEXT
#define glProgramUniformHandleui64ARB                 glgenProgramUniformHandleui64ARB
#define glProgramUniformHandleui64NV                  glgenProgramUniformHandleui64NV
#define glProgramUniformHandleui64vARB                glgenProgramUniformHandleui64vARB
#define glProgramUniformHandleui64vNV                 glgenProgramUniformHandleui64vNV
#define glProgramUniformMatrix2dv                     glgenProgramUniformMatrix2dv
#define glProgramUniformMatrix2dvEXT                  glgenProgramUniformMatrix2dvEXT
#define glProgramUniformMatrix2fv                     glgenProgramUniformMatrix2fv
#define glProgramUniformMatrix2fvEXT                  glgenProgramUniformMatrix2fvEXT
#define glProgramUniformMatrix2x3dv                   glgenProgramUniformMatrix2x3dv
#define glProgramUniformMatrix2x3dvEXT                glgenProgramUniformMatrix2x3dvEXT
#define glProgramUniformMatrix2x3fv                   glgenProgramUniformMatrix2x3fv
#define glProgramUniformMatrix2x3fvEXT                glgenProgramUniformMatrix2x3fvEXT
#define glProgramUniformMatrix2x4dv                   glgenProgramUniformMatrix2x4dv
#define glProgramUniformMatrix2x4dvEXT                glgenProgramUniformMatrix2x4dvEXT
#define glProgramUniformMatrix2x4fv                   glgenProgramUniformMatrix2x4fv
#define glProgramUniformMatrix2x4fvEXT                glgenProgramUniformMatrix2x4fvEXT
#define glProgramUniformMatrix3dv                     glgenProgramUniformMatrix3dv
#define glProgramUniformMatrix3dvEXT                  glgenProgramUniformMatrix3dvEXT
#define glProgramUniformMatrix3fv                     glgenProgramUniformMatrix3fv
#define glProgramUniformMatrix3fvEXT                  glgenProgramUniformMatrix3fvEXT
#define glProgramUniformMatrix3x2dv                   glgenProgramUniformMatrix3x2dv
#define glProgramUniformMatrix3x2dvEXT                glgenProgramUniformMatrix3x2dvEXT
#define glProgramUniformMatrix3x2fv                   glgenProgramUniformMatrix3x2fv
#define glProgramUniformMatrix3x2fvEXT                glgenProgramUniformMatrix3x2fvEXT
#define glProgramUniformMatrix3x4dv                   glgenProgramUniformMatrix3x4dv
#define glProgramUniformMatrix3x4dvEXT                glgenProgramUniformMatrix3x4dvEXT
#define glProgramUniformMatrix3x4fv                   glgenProgramUniformMatrix3x4fv
#define glProgramUniformMatrix3x4fvEXT                glgenProgramUniformMatrix3x4fvEXT
#define glProgramUniformMatrix4dv                     glgenProgramUniformMatrix4dv
#define glProgramUniformMatrix4dvEXT                  glgenProgramUniformMatrix4dvEXT
#define glProgramUniformMatrix4fv                     glgenProgramUniformMatrix4fv
#define glProgramUniformMatrix4fvEXT                  glgenProgramUniformMatrix4fvEXT
#define glProgramUniformMatrix4x2dv                   glgenProgramUniformMatrix4x2dv
#define glProgramUniformMatrix4x2dvEXT                glgenProgramUniformMatrix4x2dvEXT
#define glProgramUniformMatrix4x2fv                   glgenProgramUniformMatrix4x2fv
#define glProgramUniformMatrix4x2fvEXT                glgenProgramUniformMatrix4x2fvEXT
#define glProgramUniformMatrix4x3dv                   glgenProgramUniformMatrix4x3dv
#define glProgramUniformMatrix4x3dvEXT                glgenProgramUniformMatrix4x3dvEXT
#define glProgramUniformMatrix4x3fv                   glgenProgramUniformMatrix4x3fv
#define glProgramUniformMatrix4x3fvEXT                glgenProgramUniformMatrix4x3fvEXT
#define glProgramUniformui64NV                        glgenProgramUniformui64NV
#define glProgramUniformui64vNV                       glgenProgramUniformui64vNV
#define glProvokingVertex                             glgenProvokingVertex
#define glPushClientAttribDefaultEXT                  glgenPushClientAttribDefaultEXT
#define glPushDebugGroup                              glgenPushDebugGroup
#define glPushGroupMarkerEXT                          glgenPushGroupMarkerEXT
#define glQueryCounter                                glgenQueryCounter
#define glRasterSamplesEXT                            glgenRasterSamplesEXT
#define glReadBuffer                                  glgenReadBuffer
#define glReadPixels                                  glgenReadPixels
#define glReadnPixels                                 glgenReadnPixels
#define glReadnPixelsARB                              glgenReadnPixelsARB
#define glReleaseShaderCompiler                       glgenReleaseShaderCompiler
#define glRenderbufferStorage                         glgenRenderbufferStorage
#define glRenderbufferStorageMultisample              glgenRenderbufferStorageMultisample
#define glRenderbufferStorageMultisampleAdvancedAMD   glgenRenderbufferStorageMultisampleAdvancedAMD
#define glRenderbufferStorageMultisampleCoverageNV    glgenRenderbufferStorageMultisampleCoverageNV
#define glResetMemoryObjectParameterNV                glgenResetMemoryObjectParameterNV
#define glResolveDepthValuesNV                        glgenResolveDepthValuesNV
#define glResumeTransformFeedback                     glgenResumeTransformFeedback
#define glSampleCoverage                              glgenSampleCoverage
#define glSampleMaski                                 glgenSampleMaski
#define glSamplerParameterIiv                         glgenSamplerParameterIiv
#define glSamplerParameterIuiv                        glgenSamplerParameterIuiv
#define glSamplerParameterf                           glgenSamplerParameterf
#define glSamplerParameterfv                          glgenSamplerParameterfv
#define glSamplerParameteri                           glgenSamplerParameteri
#define glSamplerParameteriv                          glgenSamplerParameteriv
#define glScissor                                     glgenScissor
#define glScissorArrayv                               glgenScissorArrayv
#define glScissorExclusiveArrayvNV                    glgenScissorExclusiveArrayvNV
#define glScissorExclusiveNV                          glgenScissorExclusiveNV
#define glScissorIndexed                              glgenScissorIndexed
#define glScissorIndexedv                             glgenScissorIndexedv
#define glSecondaryColorFormatNV                      glgenSecondaryColorFormatNV
#define glSelectPerfMonitorCountersAMD                glgenSelectPerfMonitorCountersAMD
#define glShaderBinary                                glgenShaderBinary
#define glShaderSource                                glgenShaderSource
#define glShaderStorageBlockBinding                   glgenShaderStorageBlockBinding
#define glShadingRateImageBarrierNV                   glgenShadingRateImageBarrierNV
#define glShadingRateImagePaletteNV                   glgenShadingRateImagePaletteNV
#define glShadingRateSampleOrderCustomNV              glgenShadingRateSampleOrderCustomNV
#define glShadingRateSampleOrderNV                    glgenShadingRateSampleOrderNV
#define glSignalVkFenceNV                             glgenSignalVkFenceNV
#define glSignalVkSemaphoreNV                         glgenSignalVkSemaphoreNV
#define glSpecializeShader                            glgenSpecializeShader
#define glSpecializeShaderARB                         glgenSpecializeShaderARB
#define glStateCaptureNV                              glgenStateCaptureNV
#define glStencilFillPathInstancedNV                  glgenStencilFillPathInstancedNV
#define glStencilFillPathNV                           glgenStencilFillPathNV
#define glStencilFunc                                 glgenStencilFunc
#define glStencilFuncSeparate                         glgenStencilFuncSeparate
#define glStencilMask                                 glgenStencilMask
#define glStencilMaskSeparate                         glgenStencilMaskSeparate
#define glStencilOp                                   glgenStencilOp
#define glStencilOpSeparate                           glgenStencilOpSeparate
#define glStencilStrokePathInstancedNV                glgenStencilStrokePathInstancedNV
#define glStencilStrokePathNV                         glgenStencilStrokePathNV
#define glStencilThenCoverFillPathInstancedNV         glgenStencilThenCoverFillPathInstancedNV
#define glStencilThenCoverFillPathNV                  glgenStencilThenCoverFillPathNV
#define glStencilThenCoverStrokePathInstancedNV       glgenStencilThenCoverStrokePathInstancedNV
#define glStencilThenCoverStrokePathNV                glgenStencilThenCoverStrokePathNV
#define glSubpixelPrecisionBiasNV                     glgenSubpixelPrecisionBiasNV
#define glTexAttachMemoryNV                           glgenTexAttachMemoryNV
#define glTexBuffer                                   glgenTexBuffer
#define glTexBufferARB                                glgenTexBufferARB
#define glTexBufferRange                              glgenTexBufferRange
#define glTexCoordFormatNV                            glgenTexCoordFormatNV
#define glTexImage1D                                  glgenTexImage1D
#define glTexImage2D                                  glgenTexImage2D
#define glTexImage2DMultisample                       glgenTexImage2DMultisample
#define glTexImage3D                                  glgenTexImage3D
#define glTexImage3DMultisample                       glgenTexImage3DMultisample
#define glTexPageCommitmentARB                        glgenTexPageCommitmentARB
#define glTexParameterIiv                             glgenTexParameterIiv
#define glTexParameterIuiv                            glgenTexParameterIuiv
#define glTexParameterf                               glgenTexParameterf
#define glTexParameterfv                              glgenTexParameterfv
#define glTexParameteri                               glgenTexParameteri
#define glTexParameteriv                              glgenTexParameteriv
#define glTexStorage1D                                glgenTexStorage1D
#define glTexStorage2D                                glgenTexStorage2D
#define glTexStorage2DMultisample                     glgenTexStorage2DMultisample
#define glTexStorage3D                                glgenTexStorage3D
#define glTexStorage3DMultisample                     glgenTexStorage3DMultisample
#define glTexSubImage1D                               glgenTexSubImage1D
#define glTexSubImage2D                               glgenTexSubImage2D
#define glTexSubImage3D                               glgenTexSubImage3D
#define glTextureAttachMemoryNV                       glgenTextureAttachMemoryNV
#define glTextureBarrier                              glgenTextureBarrier
#define glTextureBarrierNV                            glgenTextureBarrierNV
#define glTextureBuffer                               glgenTextureBuffer
#define glTextureBufferEXT                            glgenTextureBufferEXT
#define glTextureBufferRange                          glgenTextureBufferRange
#define glTextureBufferRangeEXT                       glgenTextureBufferRangeEXT
#define glTextureImage1DEXT                           glgenTextureImage1DEXT
#define glTextureImage2DEXT                           glgenTextureImage2DEXT
#define glTextureImage3DEXT                           glgenTextureImage3DEXT
#define glTexturePageCommitmentEXT                    glgenTexturePageCommitmentEXT
#define glTextureParameterIiv                         glgenTextureParameterIiv
#define glTextureParameterIivEXT                      glgenTextureParameterIivEXT
#define glTextureParameterIuiv                        glgenTextureParameterIuiv
#define glTextureParameterIuivEXT                     glgenTextureParameterIuivEXT
#define glTextureParameterf                           glgenTextureParameterf
#define glTextureParameterfEXT                        glgenTextureParameterfEXT
#define glTextureParameterfv                          glgenTextureParameterfv
#define glTextureParameterfvEXT                       glgenTextureParameterfvEXT
#define glTextureParameteri                           glgenTextureParameteri
#define glTextureParameteriEXT                        glgenTextureParameteriEXT
#define glTextureParameteriv                          glgenTextureParameteriv
#define glTextureParameterivEXT                       glgenTextureParameterivEXT
#define glTextureRenderbufferEXT                      glgenTextureRenderbufferEXT
#define glTextureStorage1D                            glgenTextureStorage1D
#define glTextureStorage1DEXT                         glgenTextureStorage1DEXT
#define glTextureStorage2D                            glgenTextureStorage2D
#define glTextureStorage2DEXT                         glgenTextureStorage2DEXT
#define glTextureStorage2DMultisample                 glgenTextureStorage2DMultisample
#define glTextureStorage2DMultisampleEXT              glgenTextureStorage2DMultisampleEXT
#define glTextureStorage3D                            glgenTextureStorage3D
#define glTextureStorage3DEXT                         glgenTextureStorage3DEXT
#define glTextureStorage3DMultisample                 glgenTextureStorage3DMultisample
#define glTextureStorage3DMultisampleEXT              glgenTextureStorage3DMultisampleEXT
#define glTextureSubImage1D                           glgenTextureSubImage1D
#define glTextureSubImage1DEXT                        glgenTextureSubImage1DEXT
#define glTextureSubImage2D                           glgenTextureSubImage2D
#define glTextureSubImage2DEXT                        glgenTextureSubImage2DEXT
#define glTextureSubImage3D                           glgenTextureSubImage3D
#define glTextureSubImage3DEXT                        glgenTextureSubImage3DEXT
#define glTextureView                                 glgenTextureView
#define glTransformFeedbackBufferBase                 glgenTransformFeedbackBufferBase
#define glTransformFeedbackBufferRange                glgenTransformFeedbackBufferRange
#define glTransformFeedbackVaryings                   glgenTransformFeedbackVaryings
#define glTransformPathNV                             glgenTransformPathNV
#define glUniform1d                                   glgenUniform1d
#define glUniform1dv                                  glgenUniform1dv
#define glUniform1f                                   glgenUniform1f
#define glUniform1fv                                  glgenUniform1fv
#define glUniform1i                                   glgenUniform1i
#define glUniform1i64ARB                              glgenUniform1i64ARB
#define glUniform1i64NV                               glgenUniform1i64NV
#define glUniform1i64vARB                             glgenUniform1i64vARB
#define glUniform1i64vNV                              glgenUniform1i64vNV
#define glUniform1iv                                  glgenUniform1iv
#define glUniform1ui                                  glgenUniform1ui
#define glUniform1ui64ARB                             glgenUniform1ui64ARB
#define glUniform1ui64NV                              glgenUniform1ui64NV
#define glUniform1ui64vARB                            glgenUniform1ui64vARB
#define glUniform1ui64vNV                             glgenUniform1ui64vNV
#define glUniform1uiv                                 glgenUniform1uiv
#define glUniform2d                                   glgenUniform2d
#define glUniform2dv                                  glgenUniform2dv
#define glUniform2f                                   glgenUniform2f
#define glUniform2fv                                  glgenUniform2fv
#define glUniform2i                                   glgenUniform2i
#define glUniform2i64ARB                              glgenUniform2i64ARB
#define glUniform2i64NV                               glgenUniform2i64NV
#define glUniform2i64vARB                             glgenUniform2i64vARB
#define glUniform2i64vNV                              glgenUniform2i64vNV
#define glUniform2iv                                  glgenUniform2iv
#define glUniform2ui                                  glgenUniform2ui
#define glUniform2ui64ARB                             glgenUniform2ui64ARB
#define glUniform2ui64NV                              glgenUniform2ui64NV
#define glUniform2ui64vARB                            glgenUniform2ui64vARB
#define glUniform2ui64vNV                             glgenUniform2ui64vNV
#define glUniform2uiv                                 glgenUniform2uiv
#define glUniform3d                                   glgenUniform3d
#define glUniform3dv                                  glgenUniform3dv
#define glUniform3f                                   glgenUniform3f
#define glUniform3fv                                  glgenUniform3fv
#define glUniform3i                                   glgenUniform3i
#define glUniform3i64ARB                              glgenUniform3i64ARB
#define glUniform3i64NV                               glgenUniform3i64NV
#define glUniform3i64vARB                             glgenUniform3i64vARB
#define glUniform3i64vNV                              glgenUniform3i64vNV
#define glUniform3iv                                  glgenUniform3iv
#define glUniform3ui                                  glgenUniform3ui
#define glUniform3ui64ARB                             glgenUniform3ui64ARB
#define glUniform3ui64NV                              glgenUniform3ui64NV
#define glUniform3ui64vARB                            glgenUniform3ui64vARB
#define glUniform3ui64vNV                             glgenUniform3ui64vNV
#define glUniform3uiv                                 glgenUniform3uiv
#define glUniform4d                                   glgenUniform4d
#define glUniform4dv                                  glgenUniform4dv
#define glUniform4f                                   glgenUniform4f
#define glUniform4fv                                  glgenUniform4fv
#define glUniform4i                                   glgenUniform4i
#define glUniform4i64ARB                              glgenUniform4i64ARB
#define glUniform4i64NV                               glgenUniform4i64NV
#define glUniform4i64vARB                             glgenUniform4i64vARB
#define glUniform4i64vNV                              glgenUniform4i64vNV
#define glUniform4iv                                  glgenUniform4iv
#define glUniform4ui                                  glgenUniform4ui
#define glUniform4ui64ARB                             glgenUniform4ui64ARB
#define glUniform4ui64NV                              glgenUniform4ui64NV
#define glUniform4ui64vARB                            glgenUniform4ui64vARB
#define glUniform4ui64vNV                             glgenUniform4ui64vNV
#define glUniform4uiv                                 glgenUniform4uiv
#define glUniformBlockBinding                         glgenUniformBlockBinding
#define glUniformHandleui64ARB                        glgenUniformHandleui64ARB
#define glUniformHandleui64NV                         glgenUniformHandleui64NV
#define glUniformHandleui64vARB                       glgenUniformHandleui64vARB
#define glUniformHandleui64vNV                        glgenUniformHandleui64vNV
#define glUniformMatrix2dv                            glgenUniformMatrix2dv
#define glUniformMatrix2fv                            glgenUniformMatrix2fv
#define glUniformMatrix2x3dv                          glgenUniformMatrix2x3dv
#define glUniformMatrix2x3fv                          glgenUniformMatrix2x3fv
#define glUniformMatrix2x4dv                          glgenUniformMatrix2x4dv
#define glUniformMatrix2x4fv                          glgenUniformMatrix2x4fv
#define glUniformMatrix3dv                            glgenUniformMatrix3dv
#define glUniformMatrix3fv                            glgenUniformMatrix3fv
#define glUniformMatrix3x2dv                          glgenUniformMatrix3x2dv
#define glUniformMatrix3x2fv                          glgenUniformMatrix3x2fv
#define glUniformMatrix3x4dv                          glgenUniformMatrix3x4dv
#define glUniformMatrix3x4fv                          glgenUniformMatrix3x4fv
#define glUniformMatrix4dv                            glgenUniformMatrix4dv
#define glUniformMatrix4fv                            glgenUniformMatrix4fv
#define glUniformMatrix4x2dv                          glgenUniformMatrix4x2dv
#define glUniformMatrix4x2fv                          glgenUniformMatrix4x2fv
#define glUniformMatrix4x3dv                          glgenUniformMatrix4x3dv
#define glUniformMatrix4x3fv                          glgenUniformMatrix4x3fv
#define glUniformSubroutinesuiv                       glgenUniformSubroutinesuiv
#define glUniformui64NV                               glgenUniformui64NV
#define glUniformui64vNV                              glgenUniformui64vNV
#define glUnmapBuffer                                 glgenUnmapBuffer
#define glUnmapNamedBuffer                            glgenUnmapNamedBuffer
#define glUnmapNamedBufferEXT                         glgenUnmapNamedBufferEXT
#define glUseProgram                                  glgenUseProgram
#define glUseProgramStages                            glgenUseProgramStages
#define glUseShaderProgramEXT                         glgenUseShaderProgramEXT
#define glValidateProgram                             glgenValidateProgram
#define glValidateProgramPipeline                     glgenValidateProgramPipeline
#define glVertexArrayAttribBinding                    glgenVertexArrayAttribBinding
#define glVertexArrayAttribFormat                     glgenVertexArrayAttribFormat
#define glVertexArrayAttribIFormat                    glgenVertexArrayAttribIFormat
#define glVertexArrayAttribLFormat                    glgenVertexArrayAttribLFormat
#define glVertexArrayBindVertexBufferEXT              glgenVertexArrayBindVertexBufferEXT
#define glVertexArrayBindingDivisor                   glgenVertexArrayBindingDivisor
#define glVertexArrayColorOffsetEXT                   glgenVertexArrayColorOffsetEXT
#define glVertexArrayEdgeFlagOffsetEXT                glgenVertexArrayEdgeFlagOffsetEXT
#define glVertexArrayElementBuffer                    glgenVertexArrayElementBuffer
#define glVertexArrayFogCoordOffsetEXT                glgenVertexArrayFogCoordOffsetEXT
#define glVertexArrayIndexOffsetEXT                   glgenVertexArrayIndexOffsetEXT
#define glVertexArrayMultiTexCoordOffsetEXT           glgenVertexArrayMultiTexCoordOffsetEXT
#define glVertexArrayNormalOffsetEXT                  glgenVertexArrayNormalOffsetEXT
#define glVertexArraySecondaryColorOffsetEXT          glgenVertexArraySecondaryColorOffsetEXT
#define glVertexArrayTexCoordOffsetEXT                glgenVertexArrayTexCoordOffsetEXT
#define glVertexArrayVertexAttribBindingEXT           glgenVertexArrayVertexAttribBindingEXT
#define glVertexArrayVertexAttribDivisorEXT           glgenVertexArrayVertexAttribDivisorEXT
#define glVertexArrayVertexAttribFormatEXT            glgenVertexArrayVertexAttribFormatEXT
#define glVertexArrayVertexAttribIFormatEXT           glgenVertexArrayVertexAttribIFormatEXT
#define glVertexArrayVertexAttribIOffsetEXT           glgenVertexArrayVertexAttribIOffsetEXT
#define glVertexArrayVertexAttribLFormatEXT           glgenVertexArrayVertexAttribLFormatEXT
#define glVertexArrayVertexAttribLOffsetEXT           glgenVertexArrayVertexAttribLOffsetEXT
#define glVertexArrayVertexAttribOffsetEXT            glgenVertexArrayVertexAttribOffsetEXT
#define glVertexArrayVertexBindingDivisorEXT          glgenVertexArrayVertexBindingDivisorEXT
#define glVertexArrayVertexBuffer                     glgenVertexArrayVertexBuffer
#define glVertexArrayVertexBuffers                    glgenVertexArrayVertexBuffers
#define glVertexArrayVertexOffsetEXT                  glgenVertexArrayVertexOffsetEXT
#define glVertexAttrib1d                              glgenVertexAttrib1d
#define glVertexAttrib1dv                             glgenVertexAttrib1dv
#define glVertexAttrib1f                              glgenVertexAttrib1f
#define glVertexAttrib1fv                             glgenVertexAttrib1fv
#define glVertexAttrib1s                              glgenVertexAttrib1s
#define glVertexAttrib1sv                             glgenVertexAttrib1sv
#define glVertexAttrib2d                              glgenVertexAttrib2d
#define glVertexAttrib2dv                             glgenVertexAttrib2dv
#define glVertexAttrib2f                              glgenVertexAttrib2f
#define glVertexAttrib2fv                             glgenVertexAttrib2fv
#define glVertexAttrib2s                              glgenVertexAttrib2s
#define glVertexAttrib2sv                             glgenVertexAttrib2sv
#define glVertexAttrib3d                              glgenVertexAttrib3d
#define glVertexAttrib3dv                             glgenVertexAttrib3dv
#define glVertexAttrib3f                              glgenVertexAttrib3f
#define glVertexAttrib3fv                             glgenVertexAttrib3fv
#define glVertexAttrib3s                              glgenVertexAttrib3s
#define glVertexAttrib3sv                             glgenVertexAttrib3sv
#define glVertexAttrib4Nbv                            glgenVertexAttrib4Nbv
#define glVertexAttrib4Niv                            glgenVertexAttrib4Niv
#define glVertexAttrib4Nsv                            glgenVertexAttrib4Nsv
#define glVertexAttrib4Nub                            glgenVertexAttrib4Nub
#define glVertexAttrib4Nubv                           glgenVertexAttrib4Nubv
#define glVertexAttrib4Nuiv                           glgenVertexAttrib4Nuiv
#define glVertexAttrib4Nusv                           glgenVertexAttrib4Nusv
#define glVertexAttrib4bv                             glgenVertexAttrib4bv
#define glVertexAttrib4d                              glgenVertexAttrib4d
#define glVertexAttrib4dv                             glgenVertexAttrib4dv
#define glVertexAttrib4f                              glgenVertexAttrib4f
#define glVertexAttrib4fv                             glgenVertexAttrib4fv
#define glVertexAttrib4iv                             glgenVertexAttrib4iv
#define glVertexAttrib4s                              glgenVertexAttrib4s
#define glVertexAttrib4sv                             glgenVertexAttrib4sv
#define glVertexAttrib4ubv                            glgenVertexAttrib4ubv
#define glVertexAttrib4uiv                            glgenVertexAttrib4uiv
#define glVertexAttrib4usv                            glgenVertexAttrib4usv
#define glVertexAttribBinding                         glgenVertexAttribBinding
#define glVertexAttribDivisor                         glgenVertexAttribDivisor
#define glVertexAttribDivisorARB                      glgenVertexAttribDivisorARB
#define glVertexAttribFormat                          glgenVertexAttribFormat
#define glVertexAttribFormatNV                        glgenVertexAttribFormatNV
#define glVertexAttribI1i                             glgenVertexAttribI1i
#define glVertexAttribI1iv                            glgenVertexAttribI1iv
#define glVertexAttribI1ui                            glgenVertexAttribI1ui
#define glVertexAttribI1uiv                           glgenVertexAttribI1uiv
#define glVertexAttribI2i                             glgenVertexAttribI2i
#define glVertexAttribI2iv                            glgenVertexAttribI2iv
#define glVertexAttribI2ui                            glgenVertexAttribI2ui
#define glVertexAttribI2uiv                           glgenVertexAttribI2uiv
#define glVertexAttribI3i                             glgenVertexAttribI3i
#define glVertexAttribI3iv                            glgenVertexAttribI3iv
#define glVertexAttribI3ui                            glgenVertexAttribI3ui
#define glVertexAttribI3uiv                           glgenVertexAttribI3uiv
#define glVertexAttribI4bv                            glgenVertexAttribI4bv
#define glVertexAttribI4i                             glgenVertexAttribI4i
#define glVertexAttribI4iv                            glgenVertexAttribI4iv
#define glVertexAttribI4sv                            glgenVertexAttribI4sv
#define glVertexAttribI4ubv                           glgenVertexAttribI4ubv
#define glVertexAttribI4ui                            glgenVertexAttribI4ui
#define glVertexAttribI4uiv                           glgenVertexAttribI4uiv
#define glVertexAttribI4usv                           glgenVertexAttribI4usv
#define glVertexAttribIFormat                         glgenVertexAttribIFormat
#define glVertexAttribIFormatNV                       glgenVertexAttribIFormatNV
#define glVertexAttribIPointer                        glgenVertexAttribIPointer
#define glVertexAttribL1d                             glgenVertexAttribL1d
#define glVertexAttribL1dv                            glgenVertexAttribL1dv
#define glVertexAttribL1i64NV                         glgenVertexAttribL1i64NV
#define glVertexAttribL1i64vNV                        glgenVertexAttribL1i64vNV
#define glVertexAttribL1ui64ARB                       glgenVertexAttribL1ui64ARB
#define glVertexAttribL1ui64NV                        glgenVertexAttribL1ui64NV
#define glVertexAttribL1ui64vARB                      glgenVertexAttribL1ui64vARB
#define glVertexAttribL1ui64vNV                       glgenVertexAttribL1ui64vNV
#define glVertexAttribL2d                             glgenVertexAttribL2d
#define glVertexAttribL2dv                            glgenVertexAttribL2dv
#define glVertexAttribL2i64NV                         glgenVertexAttribL2i64NV
#define glVertexAttribL2i64vNV                        glgenVertexAttribL2i64vNV
#define glVertexAttribL2ui64NV                        glgenVertexAttribL2ui64NV
#define glVertexAttribL2ui64vNV                       glgenVertexAttribL2ui64vNV
#define glVertexAttribL3d                             glgenVertexAttribL3d
#define glVertexAttribL3dv                            glgenVertexAttribL3dv
#define glVertexAttribL3i64NV                         glgenVertexAttribL3i64NV
#define glVertexAttribL3i64vNV                        glgenVertexAttribL3i64vNV
#define glVertexAttribL3ui64NV                        glgenVertexAttribL3ui64NV
#define glVertexAttribL3ui64vNV                       glgenVertexAttribL3ui64vNV
#define glVertexAttribL4d                             glgenVertexAttribL4d
#define glVertexAttribL4dv                            glgenVertexAttribL4dv
#define glVertexAttribL4i64NV                         glgenVertexAttribL4i64NV
#define glVertexAttribL4i64vNV                        glgenVertexAttribL4i64vNV
#define glVertexAttribL4ui64NV                        glgenVertexAttribL4ui64NV
#define glVertexAttribL4ui64vNV                       glgenVertexAttribL4ui64vNV
#define glVertexAttribLFormat                         glgenVertexAttribLFormat
#define glVertexAttribLFormatNV                       glgenVertexAttribLFormatNV
#define glVertexAttribLPointer                        glgenVertexAttribLPointer
#define glVertexAttribP1ui                            glgenVertexAttribP1ui
#define glVertexAttribP1uiv                           glgenVertexAttribP1uiv
#define glVertexAttribP2ui                            glgenVertexAttribP2ui
#define glVertexAttribP2uiv                           glgenVertexAttribP2uiv
#define glVertexAttribP3ui                            glgenVertexAttribP3ui
#define glVertexAttribP3uiv                           glgenVertexAttribP3uiv
#define glVertexAttribP4ui                            glgenVertexAttribP4ui
#define glVertexAttribP4uiv                           glgenVertexAttribP4uiv
#define glVertexAttribPointer                         glgenVertexAttribPointer
#define glVertexBindingDivisor                        glgenVertexBindingDivisor
#define glVertexFormatNV                              glgenVertexFormatNV
#define glViewport                                    glgenViewport
#define glViewportArrayv                              glgenViewportArrayv
#define glViewportIndexedf                            glgenViewportIndexedf
#define glViewportIndexedfv                           glgenViewportIndexedfv
#define glViewportPositionWScaleNV                    glgenViewportPositionWScaleNV
#define glViewportSwizzleNV                           glgenViewportSwizzleNV
#define glWaitSync                                    glgenWaitSync
#define glWaitVkSemaphoreNV                           glgenWaitVkSemaphoreNV
#define glWeightPathsNV                               glgenWeightPathsNV
#define glWindowRectanglesEXT                         glgenWindowRectanglesEXT

#ifdef __cplusplus
}
#endif

#endif

#if defined(ZPL_GLGEN_IMPLEMENTATION) && !defined(ZPL_GLGEN_IMPLEMENTATION_DONE)
#define ZPL_GLGEN_IMPLEMENTATION_DONE

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN 1
#define WIN32_MEAN_AND_LEAN 1
#include <windows.h>

static HMODULE zpl__glgen_libgl;

static void zpl__glgen_open_libgl (void) { zpl__glgen_libgl = LoadLibraryA("opengl32.dll"); }
static void zpl__glgen_close_libgl(void) { FreeLibrary(zpl__glgen_libgl); }

static zpl_gl3WglProc zpl__glgen_get_proc(char const *proc)
{
	zpl_gl3WglProc res;

	res = (zpl_gl3WglProc) wglGetProcAddress(proc);
	if (!res)
		res = (zpl_gl3WglProc) GetProcAddress(zpl__glgen_libgl, proc);
	return res;
}

#elif defined(__APPLE__) || defined(__APPLE_CC__)

#include <Carbon/Carbon.h>

CFBundleRef zpl__glgen_bundle;
CFURLRef zpl__glgen_bundleURL;

static void zpl__glgen_open_libgl(void)
{
	zpl__glgen_bundleURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
		CFSTR("/System/Library/Frameworks/OpenGL.framework"),
		kCFURLPOSIXPathStyle, true);

	zpl__glgen_bundle = CFBundleCreate(kCFAllocatorDefault, zpl__glgen_bundleURL);
	assert(zpl__glgen_bundle != NULL);
}

static void zpl__glgen_close_libgl(void)
{
	CFRelease(zpl__glgen_bundle);
	CFRelease(zpl__glgen_bundleURL);
}

static GLGENglProc zpl__glgen_get_proc(char const *proc)
{
	GLGENglProc res;

	CFStringRef procname = CFStringCreateWithCString(kCFAllocatorDefault, proc,
		kCFStringEncodingASCII);
	res = (GLGENglProc) CFBundleGetFunctionPointerForName(zpl__glgen_bundle, procname);
	CFRelease(procname);
	return res;
}

#else

#include <dlfcn.h>
#include <GL/glx.h>

static void *zpl__glgen_libgl;
static PFNGLXGETPROCADDRESSPROC zpl__glgen_glx_get_proc_address;

static void zpl__glgen_open_libgl(void)
{
	zpl__glgen_libgl = dlopen("libGL.so.1", RTLD_LAZY | RTLD_GLOBAL);
	zpl__glgen_glx_get_proc_address = (PFNGLXGETPROCADDRESSPROC) dlsym(zpl__glgen_libgl, "glXGetProcAddressARB");
}

static void zpl__glgen_close_libgl(void) { dlclose(zpl__glgen_libgl); }

static zpl_gl3WglProc zpl__glgen_get_proc(char const *proc)
{
	zpl_gl3WglProc res;

	res = (zpl_gl3WglProc) zpl__glgen_glx_get_proc_address((const GLubyte *) proc);
	if (!res)
		res = (zpl_gl3WglProc) dlsym(zpl__glgen_libgl, proc);
	return res;
}

#endif

static struct {
	int major, minor;
} zpl__glgen_version;

static int zpl__glgen_parse_version(void)
{
	if (!glGetIntegerv)
		return -1;

	glGetIntegerv(GL_MAJOR_VERSION, &zpl__glgen_version.major);
	glGetIntegerv(GL_MINOR_VERSION, &zpl__glgen_version.minor);

	if (zpl__glgen_version.major < 3)
		return -1;
	return 0;
}

static void zpl__glgen_load_procs(void);

int zpl_glgen_init(void)
{
	zpl__glgen_open_libgl();
	zpl__glgen_load_procs();
	zpl__glgen_close_libgl();
	return zpl__glgen_parse_version();
}

int zpl_glgen_is_supported(int major, int minor)
{
	if (major < 3)
		return 0;
	if (zpl__glgen_version.major == major)
		return zpl__glgen_version.minor >= minor;
	return zpl__glgen_version.major >= major;
}

zpl_gl3WglProc zpl_glgen_get_proc_address(char const *proc)
{
	return zpl__glgen_get_proc(proc);
}

PFNGLACTIVEPROGRAMEXTPROC                            glgenActiveProgramEXT;
PFNGLACTIVESHADERPROGRAMPROC                         glgenActiveShaderProgram;
PFNGLACTIVETEXTUREPROC                               glgenActiveTexture;
PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC         glgenApplyFramebufferAttachmentCMAAINTEL;
PFNGLATTACHSHADERPROC                                glgenAttachShader;
PFNGLBEGINCONDITIONALRENDERPROC                      glgenBeginConditionalRender;
PFNGLBEGINCONDITIONALRENDERNVPROC                    glgenBeginConditionalRenderNV;
PFNGLBEGINPERFMONITORAMDPROC                         glgenBeginPerfMonitorAMD;
PFNGLBEGINPERFQUERYINTELPROC                         glgenBeginPerfQueryINTEL;
PFNGLBEGINQUERYPROC                                  glgenBeginQuery;
PFNGLBEGINQUERYINDEXEDPROC                           glgenBeginQueryIndexed;
PFNGLBEGINTRANSFORMFEEDBACKPROC                      glgenBeginTransformFeedback;
PFNGLBINDATTRIBLOCATIONPROC                          glgenBindAttribLocation;
PFNGLBINDBUFFERPROC                                  glgenBindBuffer;
PFNGLBINDBUFFERBASEPROC                              glgenBindBufferBase;
PFNGLBINDBUFFERRANGEPROC                             glgenBindBufferRange;
PFNGLBINDBUFFERSBASEPROC                             glgenBindBuffersBase;
PFNGLBINDBUFFERSRANGEPROC                            glgenBindBuffersRange;
PFNGLBINDFRAGDATALOCATIONPROC                        glgenBindFragDataLocation;
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC                 glgenBindFragDataLocationIndexed;
PFNGLBINDFRAMEBUFFERPROC                             glgenBindFramebuffer;
PFNGLBINDIMAGETEXTUREPROC                            glgenBindImageTexture;
PFNGLBINDIMAGETEXTURESPROC                           glgenBindImageTextures;
PFNGLBINDMULTITEXTUREEXTPROC                         glgenBindMultiTextureEXT;
PFNGLBINDPROGRAMPIPELINEPROC                         glgenBindProgramPipeline;
PFNGLBINDRENDERBUFFERPROC                            glgenBindRenderbuffer;
PFNGLBINDSAMPLERPROC                                 glgenBindSampler;
PFNGLBINDSAMPLERSPROC                                glgenBindSamplers;
PFNGLBINDSHADINGRATEIMAGENVPROC                      glgenBindShadingRateImageNV;
PFNGLBINDTEXTUREPROC                                 glgenBindTexture;
PFNGLBINDTEXTUREUNITPROC                             glgenBindTextureUnit;
PFNGLBINDTEXTURESPROC                                glgenBindTextures;
PFNGLBINDTRANSFORMFEEDBACKPROC                       glgenBindTransformFeedback;
PFNGLBINDVERTEXARRAYPROC                             glgenBindVertexArray;
PFNGLBINDVERTEXBUFFERPROC                            glgenBindVertexBuffer;
PFNGLBINDVERTEXBUFFERSPROC                           glgenBindVertexBuffers;
PFNGLBLENDBARRIERKHRPROC                             glgenBlendBarrierKHR;
PFNGLBLENDBARRIERNVPROC                              glgenBlendBarrierNV;
PFNGLBLENDCOLORPROC                                  glgenBlendColor;
PFNGLBLENDEQUATIONPROC                               glgenBlendEquation;
PFNGLBLENDEQUATIONSEPARATEPROC                       glgenBlendEquationSeparate;
PFNGLBLENDEQUATIONSEPARATEIPROC                      glgenBlendEquationSeparatei;
PFNGLBLENDEQUATIONSEPARATEIARBPROC                   glgenBlendEquationSeparateiARB;
PFNGLBLENDEQUATIONIPROC                              glgenBlendEquationi;
PFNGLBLENDEQUATIONIARBPROC                           glgenBlendEquationiARB;
PFNGLBLENDFUNCPROC                                   glgenBlendFunc;
PFNGLBLENDFUNCSEPARATEPROC                           glgenBlendFuncSeparate;
PFNGLBLENDFUNCSEPARATEIPROC                          glgenBlendFuncSeparatei;
PFNGLBLENDFUNCSEPARATEIARBPROC                       glgenBlendFuncSeparateiARB;
PFNGLBLENDFUNCIPROC                                  glgenBlendFunci;
PFNGLBLENDFUNCIARBPROC                               glgenBlendFunciARB;
PFNGLBLENDPARAMETERINVPROC                           glgenBlendParameteriNV;
PFNGLBLITFRAMEBUFFERPROC                             glgenBlitFramebuffer;
PFNGLBLITNAMEDFRAMEBUFFERPROC                        glgenBlitNamedFramebuffer;
PFNGLBUFFERADDRESSRANGENVPROC                        glgenBufferAddressRangeNV;
PFNGLBUFFERATTACHMEMORYNVPROC                        glgenBufferAttachMemoryNV;
PFNGLBUFFERDATAPROC                                  glgenBufferData;
PFNGLBUFFERPAGECOMMITMENTARBPROC                     glgenBufferPageCommitmentARB;
PFNGLBUFFERSTORAGEPROC                               glgenBufferStorage;
PFNGLBUFFERSUBDATAPROC                               glgenBufferSubData;
PFNGLCALLCOMMANDLISTNVPROC                           glgenCallCommandListNV;
PFNGLCHECKFRAMEBUFFERSTATUSPROC                      glgenCheckFramebufferStatus;
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC                 glgenCheckNamedFramebufferStatus;
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC              glgenCheckNamedFramebufferStatusEXT;
PFNGLCLAMPCOLORPROC                                  glgenClampColor;
PFNGLCLEARPROC                                       glgenClear;
PFNGLCLEARBUFFERDATAPROC                             glgenClearBufferData;
PFNGLCLEARBUFFERSUBDATAPROC                          glgenClearBufferSubData;
PFNGLCLEARBUFFERFIPROC                               glgenClearBufferfi;
PFNGLCLEARBUFFERFVPROC                               glgenClearBufferfv;
PFNGLCLEARBUFFERIVPROC                               glgenClearBufferiv;
PFNGLCLEARBUFFERUIVPROC                              glgenClearBufferuiv;
PFNGLCLEARCOLORPROC                                  glgenClearColor;
PFNGLCLEARDEPTHPROC                                  glgenClearDepth;
PFNGLCLEARDEPTHFPROC                                 glgenClearDepthf;
PFNGLCLEARNAMEDBUFFERDATAPROC                        glgenClearNamedBufferData;
PFNGLCLEARNAMEDBUFFERDATAEXTPROC                     glgenClearNamedBufferDataEXT;
PFNGLCLEARNAMEDBUFFERSUBDATAPROC                     glgenClearNamedBufferSubData;
PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC                  glgenClearNamedBufferSubDataEXT;
PFNGLCLEARNAMEDFRAMEBUFFERFIPROC                     glgenClearNamedFramebufferfi;
PFNGLCLEARNAMEDFRAMEBUFFERFVPROC                     glgenClearNamedFramebufferfv;
PFNGLCLEARNAMEDFRAMEBUFFERIVPROC                     glgenClearNamedFramebufferiv;
PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC                    glgenClearNamedFramebufferuiv;
PFNGLCLEARSTENCILPROC                                glgenClearStencil;
PFNGLCLEARTEXIMAGEPROC                               glgenClearTexImage;
PFNGLCLEARTEXSUBIMAGEPROC                            glgenClearTexSubImage;
PFNGLCLIENTATTRIBDEFAULTEXTPROC                      glgenClientAttribDefaultEXT;
PFNGLCLIENTWAITSYNCPROC                              glgenClientWaitSync;
PFNGLCLIPCONTROLPROC                                 glgenClipControl;
PFNGLCOLORFORMATNVPROC                               glgenColorFormatNV;
PFNGLCOLORMASKPROC                                   glgenColorMask;
PFNGLCOLORMASKIPROC                                  glgenColorMaski;
PFNGLCOMMANDLISTSEGMENTSNVPROC                       glgenCommandListSegmentsNV;
PFNGLCOMPILECOMMANDLISTNVPROC                        glgenCompileCommandListNV;
PFNGLCOMPILESHADERPROC                               glgenCompileShader;
PFNGLCOMPILESHADERINCLUDEARBPROC                     glgenCompileShaderIncludeARB;
PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC                glgenCompressedMultiTexImage1DEXT;
PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC                glgenCompressedMultiTexImage2DEXT;
PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC                glgenCompressedMultiTexImage3DEXT;
PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC             glgenCompressedMultiTexSubImage1DEXT;
PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC             glgenCompressedMultiTexSubImage2DEXT;
PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC             glgenCompressedMultiTexSubImage3DEXT;
PFNGLCOMPRESSEDTEXIMAGE1DPROC                        glgenCompressedTexImage1D;
PFNGLCOMPRESSEDTEXIMAGE2DPROC                        glgenCompressedTexImage2D;
PFNGLCOMPRESSEDTEXIMAGE3DPROC                        glgenCompressedTexImage3D;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC                     glgenCompressedTexSubImage1D;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC                     glgenCompressedTexSubImage2D;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC                     glgenCompressedTexSubImage3D;
PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC                 glgenCompressedTextureImage1DEXT;
PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC                 glgenCompressedTextureImage2DEXT;
PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC                 glgenCompressedTextureImage3DEXT;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC                 glgenCompressedTextureSubImage1D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC              glgenCompressedTextureSubImage1DEXT;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC                 glgenCompressedTextureSubImage2D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC              glgenCompressedTextureSubImage2DEXT;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC                 glgenCompressedTextureSubImage3D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC              glgenCompressedTextureSubImage3DEXT;
PFNGLCONSERVATIVERASTERPARAMETERFNVPROC              glgenConservativeRasterParameterfNV;
PFNGLCONSERVATIVERASTERPARAMETERINVPROC              glgenConservativeRasterParameteriNV;
PFNGLCOPYBUFFERSUBDATAPROC                           glgenCopyBufferSubData;
PFNGLCOPYIMAGESUBDATAPROC                            glgenCopyImageSubData;
PFNGLCOPYMULTITEXIMAGE1DEXTPROC                      glgenCopyMultiTexImage1DEXT;
PFNGLCOPYMULTITEXIMAGE2DEXTPROC                      glgenCopyMultiTexImage2DEXT;
PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC                   glgenCopyMultiTexSubImage1DEXT;
PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC                   glgenCopyMultiTexSubImage2DEXT;
PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC                   glgenCopyMultiTexSubImage3DEXT;
PFNGLCOPYNAMEDBUFFERSUBDATAPROC                      glgenCopyNamedBufferSubData;
PFNGLCOPYPATHNVPROC                                  glgenCopyPathNV;
PFNGLCOPYTEXIMAGE1DPROC                              glgenCopyTexImage1D;
PFNGLCOPYTEXIMAGE2DPROC                              glgenCopyTexImage2D;
PFNGLCOPYTEXSUBIMAGE1DPROC                           glgenCopyTexSubImage1D;
PFNGLCOPYTEXSUBIMAGE2DPROC                           glgenCopyTexSubImage2D;
PFNGLCOPYTEXSUBIMAGE3DPROC                           glgenCopyTexSubImage3D;
PFNGLCOPYTEXTUREIMAGE1DEXTPROC                       glgenCopyTextureImage1DEXT;
PFNGLCOPYTEXTUREIMAGE2DEXTPROC                       glgenCopyTextureImage2DEXT;
PFNGLCOPYTEXTURESUBIMAGE1DPROC                       glgenCopyTextureSubImage1D;
PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC                    glgenCopyTextureSubImage1DEXT;
PFNGLCOPYTEXTURESUBIMAGE2DPROC                       glgenCopyTextureSubImage2D;
PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC                    glgenCopyTextureSubImage2DEXT;
PFNGLCOPYTEXTURESUBIMAGE3DPROC                       glgenCopyTextureSubImage3D;
PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC                    glgenCopyTextureSubImage3DEXT;
PFNGLCOVERFILLPATHINSTANCEDNVPROC                    glgenCoverFillPathInstancedNV;
PFNGLCOVERFILLPATHNVPROC                             glgenCoverFillPathNV;
PFNGLCOVERSTROKEPATHINSTANCEDNVPROC                  glgenCoverStrokePathInstancedNV;
PFNGLCOVERSTROKEPATHNVPROC                           glgenCoverStrokePathNV;
PFNGLCOVERAGEMODULATIONNVPROC                        glgenCoverageModulationNV;
PFNGLCOVERAGEMODULATIONTABLENVPROC                   glgenCoverageModulationTableNV;
PFNGLCREATEBUFFERSPROC                               glgenCreateBuffers;
PFNGLCREATECOMMANDLISTSNVPROC                        glgenCreateCommandListsNV;
PFNGLCREATEFRAMEBUFFERSPROC                          glgenCreateFramebuffers;
PFNGLCREATEPERFQUERYINTELPROC                        glgenCreatePerfQueryINTEL;
PFNGLCREATEPROGRAMPROC                               glgenCreateProgram;
PFNGLCREATEPROGRAMPIPELINESPROC                      glgenCreateProgramPipelines;
PFNGLCREATEQUERIESPROC                               glgenCreateQueries;
PFNGLCREATERENDERBUFFERSPROC                         glgenCreateRenderbuffers;
PFNGLCREATESAMPLERSPROC                              glgenCreateSamplers;
PFNGLCREATESHADERPROC                                glgenCreateShader;
PFNGLCREATESHADERPROGRAMEXTPROC                      glgenCreateShaderProgramEXT;
PFNGLCREATESHADERPROGRAMVPROC                        glgenCreateShaderProgramv;
PFNGLCREATESTATESNVPROC                              glgenCreateStatesNV;
PFNGLCREATESYNCFROMCLEVENTARBPROC                    glgenCreateSyncFromCLeventARB;
PFNGLCREATETEXTURESPROC                              glgenCreateTextures;
PFNGLCREATETRANSFORMFEEDBACKSPROC                    glgenCreateTransformFeedbacks;
PFNGLCREATEVERTEXARRAYSPROC                          glgenCreateVertexArrays;
PFNGLCULLFACEPROC                                    glgenCullFace;
PFNGLDEBUGMESSAGECALLBACKPROC                        glgenDebugMessageCallback;
PFNGLDEBUGMESSAGECALLBACKARBPROC                     glgenDebugMessageCallbackARB;
PFNGLDEBUGMESSAGECONTROLPROC                         glgenDebugMessageControl;
PFNGLDEBUGMESSAGECONTROLARBPROC                      glgenDebugMessageControlARB;
PFNGLDEBUGMESSAGEINSERTPROC                          glgenDebugMessageInsert;
PFNGLDEBUGMESSAGEINSERTARBPROC                       glgenDebugMessageInsertARB;
PFNGLDELETEBUFFERSPROC                               glgenDeleteBuffers;
PFNGLDELETECOMMANDLISTSNVPROC                        glgenDeleteCommandListsNV;
PFNGLDELETEFRAMEBUFFERSPROC                          glgenDeleteFramebuffers;
PFNGLDELETENAMEDSTRINGARBPROC                        glgenDeleteNamedStringARB;
PFNGLDELETEPATHSNVPROC                               glgenDeletePathsNV;
PFNGLDELETEPERFMONITORSAMDPROC                       glgenDeletePerfMonitorsAMD;
PFNGLDELETEPERFQUERYINTELPROC                        glgenDeletePerfQueryINTEL;
PFNGLDELETEPROGRAMPROC                               glgenDeleteProgram;
PFNGLDELETEPROGRAMPIPELINESPROC                      glgenDeleteProgramPipelines;
PFNGLDELETEQUERIESPROC                               glgenDeleteQueries;
PFNGLDELETERENDERBUFFERSPROC                         glgenDeleteRenderbuffers;
PFNGLDELETESAMPLERSPROC                              glgenDeleteSamplers;
PFNGLDELETESHADERPROC                                glgenDeleteShader;
PFNGLDELETESTATESNVPROC                              glgenDeleteStatesNV;
PFNGLDELETESYNCPROC                                  glgenDeleteSync;
PFNGLDELETETEXTURESPROC                              glgenDeleteTextures;
PFNGLDELETETRANSFORMFEEDBACKSPROC                    glgenDeleteTransformFeedbacks;
PFNGLDELETEVERTEXARRAYSPROC                          glgenDeleteVertexArrays;
PFNGLDEPTHFUNCPROC                                   glgenDepthFunc;
PFNGLDEPTHMASKPROC                                   glgenDepthMask;
PFNGLDEPTHRANGEPROC                                  glgenDepthRange;
PFNGLDEPTHRANGEARRAYVPROC                            glgenDepthRangeArrayv;
PFNGLDEPTHRANGEINDEXEDPROC                           glgenDepthRangeIndexed;
PFNGLDEPTHRANGEFPROC                                 glgenDepthRangef;
PFNGLDETACHSHADERPROC                                glgenDetachShader;
PFNGLDISABLEPROC                                     glgenDisable;
PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC                glgenDisableClientStateIndexedEXT;
PFNGLDISABLECLIENTSTATEIEXTPROC                      glgenDisableClientStateiEXT;
PFNGLDISABLEINDEXEDEXTPROC                           glgenDisableIndexedEXT;
PFNGLDISABLEVERTEXARRAYATTRIBPROC                    glgenDisableVertexArrayAttrib;
PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC                 glgenDisableVertexArrayAttribEXT;
PFNGLDISABLEVERTEXARRAYEXTPROC                       glgenDisableVertexArrayEXT;
PFNGLDISABLEVERTEXATTRIBARRAYPROC                    glgenDisableVertexAttribArray;
PFNGLDISABLEIPROC                                    glgenDisablei;
PFNGLDISPATCHCOMPUTEPROC                             glgenDispatchCompute;
PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC                 glgenDispatchComputeGroupSizeARB;
PFNGLDISPATCHCOMPUTEINDIRECTPROC                     glgenDispatchComputeIndirect;
PFNGLDRAWARRAYSPROC                                  glgenDrawArrays;
PFNGLDRAWARRAYSINDIRECTPROC                          glgenDrawArraysIndirect;
PFNGLDRAWARRAYSINSTANCEDPROC                         glgenDrawArraysInstanced;
PFNGLDRAWARRAYSINSTANCEDARBPROC                      glgenDrawArraysInstancedARB;
PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC             glgenDrawArraysInstancedBaseInstance;
PFNGLDRAWARRAYSINSTANCEDEXTPROC                      glgenDrawArraysInstancedEXT;
PFNGLDRAWBUFFERPROC                                  glgenDrawBuffer;
PFNGLDRAWBUFFERSPROC                                 glgenDrawBuffers;
PFNGLDRAWCOMMANDSADDRESSNVPROC                       glgenDrawCommandsAddressNV;
PFNGLDRAWCOMMANDSNVPROC                              glgenDrawCommandsNV;
PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC                 glgenDrawCommandsStatesAddressNV;
PFNGLDRAWCOMMANDSSTATESNVPROC                        glgenDrawCommandsStatesNV;
PFNGLDRAWELEMENTSPROC                                glgenDrawElements;
PFNGLDRAWELEMENTSBASEVERTEXPROC                      glgenDrawElementsBaseVertex;
PFNGLDRAWELEMENTSINDIRECTPROC                        glgenDrawElementsIndirect;
PFNGLDRAWELEMENTSINSTANCEDPROC                       glgenDrawElementsInstanced;
PFNGLDRAWELEMENTSINSTANCEDARBPROC                    glgenDrawElementsInstancedARB;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC           glgenDrawElementsInstancedBaseInstance;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC             glgenDrawElementsInstancedBaseVertex;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glgenDrawElementsInstancedBaseVertexBaseInstance;
PFNGLDRAWELEMENTSINSTANCEDEXTPROC                    glgenDrawElementsInstancedEXT;
PFNGLDRAWMESHTASKSINDIRECTNVPROC                     glgenDrawMeshTasksIndirectNV;
PFNGLDRAWMESHTASKSNVPROC                             glgenDrawMeshTasksNV;
PFNGLDRAWRANGEELEMENTSPROC                           glgenDrawRangeElements;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC                 glgenDrawRangeElementsBaseVertex;
PFNGLDRAWTRANSFORMFEEDBACKPROC                       glgenDrawTransformFeedback;
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC              glgenDrawTransformFeedbackInstanced;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC                 glgenDrawTransformFeedbackStream;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC        glgenDrawTransformFeedbackStreamInstanced;
PFNGLDRAWVKIMAGENVPROC                               glgenDrawVkImageNV;
PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC                 glgenEGLImageTargetTexStorageEXT;
PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC             glgenEGLImageTargetTextureStorageEXT;
PFNGLEDGEFLAGFORMATNVPROC                            glgenEdgeFlagFormatNV;
PFNGLENABLEPROC                                      glgenEnable;
PFNGLENABLECLIENTSTATEINDEXEDEXTPROC                 glgenEnableClientStateIndexedEXT;
PFNGLENABLECLIENTSTATEIEXTPROC                       glgenEnableClientStateiEXT;
PFNGLENABLEINDEXEDEXTPROC                            glgenEnableIndexedEXT;
PFNGLENABLEVERTEXARRAYATTRIBPROC                     glgenEnableVertexArrayAttrib;
PFNGLENABLEVERTEXARRAYATTRIBEXTPROC                  glgenEnableVertexArrayAttribEXT;
PFNGLENABLEVERTEXARRAYEXTPROC                        glgenEnableVertexArrayEXT;
PFNGLENABLEVERTEXATTRIBARRAYPROC                     glgenEnableVertexAttribArray;
PFNGLENABLEIPROC                                     glgenEnablei;
PFNGLENDCONDITIONALRENDERPROC                        glgenEndConditionalRender;
PFNGLENDCONDITIONALRENDERNVPROC                      glgenEndConditionalRenderNV;
PFNGLENDPERFMONITORAMDPROC                           glgenEndPerfMonitorAMD;
PFNGLENDPERFQUERYINTELPROC                           glgenEndPerfQueryINTEL;
PFNGLENDQUERYPROC                                    glgenEndQuery;
PFNGLENDQUERYINDEXEDPROC                             glgenEndQueryIndexed;
PFNGLENDTRANSFORMFEEDBACKPROC                        glgenEndTransformFeedback;
PFNGLEVALUATEDEPTHVALUESARBPROC                      glgenEvaluateDepthValuesARB;
PFNGLFENCESYNCPROC                                   glgenFenceSync;
PFNGLFINISHPROC                                      glgenFinish;
PFNGLFLUSHPROC                                       glgenFlush;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC                      glgenFlushMappedBufferRange;
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC                 glgenFlushMappedNamedBufferRange;
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC              glgenFlushMappedNamedBufferRangeEXT;
PFNGLFOGCOORDFORMATNVPROC                            glgenFogCoordFormatNV;
PFNGLFRAGMENTCOVERAGECOLORNVPROC                     glgenFragmentCoverageColorNV;
PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC                    glgenFramebufferDrawBufferEXT;
PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC                   glgenFramebufferDrawBuffersEXT;
PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC                  glgenFramebufferFetchBarrierEXT;
PFNGLFRAMEBUFFERPARAMETERIPROC                       glgenFramebufferParameteri;
PFNGLFRAMEBUFFERPARAMETERIMESAPROC                   glgenFramebufferParameteriMESA;
PFNGLFRAMEBUFFERREADBUFFEREXTPROC                    glgenFramebufferReadBufferEXT;
PFNGLFRAMEBUFFERRENDERBUFFERPROC                     glgenFramebufferRenderbuffer;
PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC             glgenFramebufferSampleLocationsfvARB;
PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC              glgenFramebufferSampleLocationsfvNV;
PFNGLFRAMEBUFFERTEXTUREPROC                          glgenFramebufferTexture;
PFNGLFRAMEBUFFERTEXTURE1DPROC                        glgenFramebufferTexture1D;
PFNGLFRAMEBUFFERTEXTURE2DPROC                        glgenFramebufferTexture2D;
PFNGLFRAMEBUFFERTEXTURE3DPROC                        glgenFramebufferTexture3D;
PFNGLFRAMEBUFFERTEXTUREARBPROC                       glgenFramebufferTextureARB;
PFNGLFRAMEBUFFERTEXTUREFACEARBPROC                   glgenFramebufferTextureFaceARB;
PFNGLFRAMEBUFFERTEXTURELAYERPROC                     glgenFramebufferTextureLayer;
PFNGLFRAMEBUFFERTEXTURELAYERARBPROC                  glgenFramebufferTextureLayerARB;
PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC              glgenFramebufferTextureMultiviewOVR;
PFNGLFRONTFACEPROC                                   glgenFrontFace;
PFNGLGENBUFFERSPROC                                  glgenGenBuffers;
PFNGLGENFRAMEBUFFERSPROC                             glgenGenFramebuffers;
PFNGLGENPATHSNVPROC                                  glgenGenPathsNV;
PFNGLGENPERFMONITORSAMDPROC                          glgenGenPerfMonitorsAMD;
PFNGLGENPROGRAMPIPELINESPROC                         glgenGenProgramPipelines;
PFNGLGENQUERIESPROC                                  glgenGenQueries;
PFNGLGENRENDERBUFFERSPROC                            glgenGenRenderbuffers;
PFNGLGENSAMPLERSPROC                                 glgenGenSamplers;
PFNGLGENTEXTURESPROC                                 glgenGenTextures;
PFNGLGENTRANSFORMFEEDBACKSPROC                       glgenGenTransformFeedbacks;
PFNGLGENVERTEXARRAYSPROC                             glgenGenVertexArrays;
PFNGLGENERATEMIPMAPPROC                              glgenGenerateMipmap;
PFNGLGENERATEMULTITEXMIPMAPEXTPROC                   glgenGenerateMultiTexMipmapEXT;
PFNGLGENERATETEXTUREMIPMAPPROC                       glgenGenerateTextureMipmap;
PFNGLGENERATETEXTUREMIPMAPEXTPROC                    glgenGenerateTextureMipmapEXT;
PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC              glgenGetActiveAtomicCounterBufferiv;
PFNGLGETACTIVEATTRIBPROC                             glgenGetActiveAttrib;
PFNGLGETACTIVESUBROUTINENAMEPROC                     glgenGetActiveSubroutineName;
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC              glgenGetActiveSubroutineUniformName;
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC                glgenGetActiveSubroutineUniformiv;
PFNGLGETACTIVEUNIFORMPROC                            glgenGetActiveUniform;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC                   glgenGetActiveUniformBlockName;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC                     glgenGetActiveUniformBlockiv;
PFNGLGETACTIVEUNIFORMNAMEPROC                        glgenGetActiveUniformName;
PFNGLGETACTIVEUNIFORMSIVPROC                         glgenGetActiveUniformsiv;
PFNGLGETATTACHEDSHADERSPROC                          glgenGetAttachedShaders;
PFNGLGETATTRIBLOCATIONPROC                           glgenGetAttribLocation;
PFNGLGETBOOLEANINDEXEDVEXTPROC                       glgenGetBooleanIndexedvEXT;
PFNGLGETBOOLEANI_VPROC                               glgenGetBooleani_v;
PFNGLGETBOOLEANVPROC                                 glgenGetBooleanv;
PFNGLGETBUFFERPARAMETERI64VPROC                      glgenGetBufferParameteri64v;
PFNGLGETBUFFERPARAMETERIVPROC                        glgenGetBufferParameteriv;
PFNGLGETBUFFERPARAMETERUI64VNVPROC                   glgenGetBufferParameterui64vNV;
PFNGLGETBUFFERPOINTERVPROC                           glgenGetBufferPointerv;
PFNGLGETBUFFERSUBDATAPROC                            glgenGetBufferSubData;
PFNGLGETCOMMANDHEADERNVPROC                          glgenGetCommandHeaderNV;
PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC               glgenGetCompressedMultiTexImageEXT;
PFNGLGETCOMPRESSEDTEXIMAGEPROC                       glgenGetCompressedTexImage;
PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC                   glgenGetCompressedTextureImage;
PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC                glgenGetCompressedTextureImageEXT;
PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC                glgenGetCompressedTextureSubImage;
PFNGLGETCOVERAGEMODULATIONTABLENVPROC                glgenGetCoverageModulationTableNV;
PFNGLGETDEBUGMESSAGELOGPROC                          glgenGetDebugMessageLog;
PFNGLGETDEBUGMESSAGELOGARBPROC                       glgenGetDebugMessageLogARB;
PFNGLGETDOUBLEINDEXEDVEXTPROC                        glgenGetDoubleIndexedvEXT;
PFNGLGETDOUBLEI_VPROC                                glgenGetDoublei_v;
PFNGLGETDOUBLEI_VEXTPROC                             glgenGetDoublei_vEXT;
PFNGLGETDOUBLEVPROC                                  glgenGetDoublev;
PFNGLGETERRORPROC                                    glgenGetError;
PFNGLGETFIRSTPERFQUERYIDINTELPROC                    glgenGetFirstPerfQueryIdINTEL;
PFNGLGETFLOATINDEXEDVEXTPROC                         glgenGetFloatIndexedvEXT;
PFNGLGETFLOATI_VPROC                                 glgenGetFloati_v;
PFNGLGETFLOATI_VEXTPROC                              glgenGetFloati_vEXT;
PFNGLGETFLOATVPROC                                   glgenGetFloatv;
PFNGLGETFRAGDATAINDEXPROC                            glgenGetFragDataIndex;
PFNGLGETFRAGDATALOCATIONPROC                         glgenGetFragDataLocation;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC         glgenGetFramebufferAttachmentParameteriv;
PFNGLGETFRAMEBUFFERPARAMETERIVPROC                   glgenGetFramebufferParameteriv;
PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC                glgenGetFramebufferParameterivEXT;
PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC               glgenGetFramebufferParameterivMESA;
PFNGLGETGRAPHICSRESETSTATUSPROC                      glgenGetGraphicsResetStatus;
PFNGLGETGRAPHICSRESETSTATUSARBPROC                   glgenGetGraphicsResetStatusARB;
PFNGLGETIMAGEHANDLEARBPROC                           glgenGetImageHandleARB;
PFNGLGETIMAGEHANDLENVPROC                            glgenGetImageHandleNV;
PFNGLGETINTEGER64I_VPROC                             glgenGetInteger64i_v;
PFNGLGETINTEGER64VPROC                               glgenGetInteger64v;
PFNGLGETINTEGERINDEXEDVEXTPROC                       glgenGetIntegerIndexedvEXT;
PFNGLGETINTEGERI_VPROC                               glgenGetIntegeri_v;
PFNGLGETINTEGERUI64I_VNVPROC                         glgenGetIntegerui64i_vNV;
PFNGLGETINTEGERUI64VNVPROC                           glgenGetIntegerui64vNV;
PFNGLGETINTEGERVPROC                                 glgenGetIntegerv;
PFNGLGETINTERNALFORMATSAMPLEIVNVPROC                 glgenGetInternalformatSampleivNV;
PFNGLGETINTERNALFORMATI64VPROC                       glgenGetInternalformati64v;
PFNGLGETINTERNALFORMATIVPROC                         glgenGetInternalformativ;
PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC       glgenGetMemoryObjectDetachedResourcesuivNV;
PFNGLGETMULTITEXENVFVEXTPROC                         glgenGetMultiTexEnvfvEXT;
PFNGLGETMULTITEXENVIVEXTPROC                         glgenGetMultiTexEnvivEXT;
PFNGLGETMULTITEXGENDVEXTPROC                         glgenGetMultiTexGendvEXT;
PFNGLGETMULTITEXGENFVEXTPROC                         glgenGetMultiTexGenfvEXT;
PFNGLGETMULTITEXGENIVEXTPROC                         glgenGetMultiTexGenivEXT;
PFNGLGETMULTITEXIMAGEEXTPROC                         glgenGetMultiTexImageEXT;
PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC              glgenGetMultiTexLevelParameterfvEXT;
PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC              glgenGetMultiTexLevelParameterivEXT;
PFNGLGETMULTITEXPARAMETERIIVEXTPROC                  glgenGetMultiTexParameterIivEXT;
PFNGLGETMULTITEXPARAMETERIUIVEXTPROC                 glgenGetMultiTexParameterIuivEXT;
PFNGLGETMULTITEXPARAMETERFVEXTPROC                   glgenGetMultiTexParameterfvEXT;
PFNGLGETMULTITEXPARAMETERIVEXTPROC                   glgenGetMultiTexParameterivEXT;
PFNGLGETMULTISAMPLEFVPROC                            glgenGetMultisamplefv;
PFNGLGETNAMEDBUFFERPARAMETERI64VPROC                 glgenGetNamedBufferParameteri64v;
PFNGLGETNAMEDBUFFERPARAMETERIVPROC                   glgenGetNamedBufferParameteriv;
PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC                glgenGetNamedBufferParameterivEXT;
PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC              glgenGetNamedBufferParameterui64vNV;
PFNGLGETNAMEDBUFFERPOINTERVPROC                      glgenGetNamedBufferPointerv;
PFNGLGETNAMEDBUFFERPOINTERVEXTPROC                   glgenGetNamedBufferPointervEXT;
PFNGLGETNAMEDBUFFERSUBDATAPROC                       glgenGetNamedBufferSubData;
PFNGLGETNAMEDBUFFERSUBDATAEXTPROC                    glgenGetNamedBufferSubDataEXT;
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC    glgenGetNamedFramebufferAttachmentParameteriv;
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glgenGetNamedFramebufferAttachmentParameterivEXT;
PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC              glgenGetNamedFramebufferParameteriv;
PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC           glgenGetNamedFramebufferParameterivEXT;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC         glgenGetNamedProgramLocalParameterIivEXT;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC        glgenGetNamedProgramLocalParameterIuivEXT;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC          glgenGetNamedProgramLocalParameterdvEXT;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC          glgenGetNamedProgramLocalParameterfvEXT;
PFNGLGETNAMEDPROGRAMSTRINGEXTPROC                    glgenGetNamedProgramStringEXT;
PFNGLGETNAMEDPROGRAMIVEXTPROC                        glgenGetNamedProgramivEXT;
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC             glgenGetNamedRenderbufferParameteriv;
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC          glgenGetNamedRenderbufferParameterivEXT;
PFNGLGETNAMEDSTRINGARBPROC                           glgenGetNamedStringARB;
PFNGLGETNAMEDSTRINGIVARBPROC                         glgenGetNamedStringivARB;
PFNGLGETNEXTPERFQUERYIDINTELPROC                     glgenGetNextPerfQueryIdINTEL;
PFNGLGETOBJECTLABELPROC                              glgenGetObjectLabel;
PFNGLGETOBJECTLABELEXTPROC                           glgenGetObjectLabelEXT;
PFNGLGETOBJECTPTRLABELPROC                           glgenGetObjectPtrLabel;
PFNGLGETPATHCOMMANDSNVPROC                           glgenGetPathCommandsNV;
PFNGLGETPATHCOORDSNVPROC                             glgenGetPathCoordsNV;
PFNGLGETPATHDASHARRAYNVPROC                          glgenGetPathDashArrayNV;
PFNGLGETPATHLENGTHNVPROC                             glgenGetPathLengthNV;
PFNGLGETPATHMETRICRANGENVPROC                        glgenGetPathMetricRangeNV;
PFNGLGETPATHMETRICSNVPROC                            glgenGetPathMetricsNV;
PFNGLGETPATHPARAMETERFVNVPROC                        glgenGetPathParameterfvNV;
PFNGLGETPATHPARAMETERIVNVPROC                        glgenGetPathParameterivNV;
PFNGLGETPATHSPACINGNVPROC                            glgenGetPathSpacingNV;
PFNGLGETPERFCOUNTERINFOINTELPROC                     glgenGetPerfCounterInfoINTEL;
PFNGLGETPERFMONITORCOUNTERDATAAMDPROC                glgenGetPerfMonitorCounterDataAMD;
PFNGLGETPERFMONITORCOUNTERINFOAMDPROC                glgenGetPerfMonitorCounterInfoAMD;
PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC              glgenGetPerfMonitorCounterStringAMD;
PFNGLGETPERFMONITORCOUNTERSAMDPROC                   glgenGetPerfMonitorCountersAMD;
PFNGLGETPERFMONITORGROUPSTRINGAMDPROC                glgenGetPerfMonitorGroupStringAMD;
PFNGLGETPERFMONITORGROUPSAMDPROC                     glgenGetPerfMonitorGroupsAMD;
PFNGLGETPERFQUERYDATAINTELPROC                       glgenGetPerfQueryDataINTEL;
PFNGLGETPERFQUERYIDBYNAMEINTELPROC                   glgenGetPerfQueryIdByNameINTEL;
PFNGLGETPERFQUERYINFOINTELPROC                       glgenGetPerfQueryInfoINTEL;
PFNGLGETPOINTERINDEXEDVEXTPROC                       glgenGetPointerIndexedvEXT;
PFNGLGETPOINTERI_VEXTPROC                            glgenGetPointeri_vEXT;
PFNGLGETPOINTERVPROC                                 glgenGetPointerv;
PFNGLGETPROGRAMBINARYPROC                            glgenGetProgramBinary;
PFNGLGETPROGRAMINFOLOGPROC                           glgenGetProgramInfoLog;
PFNGLGETPROGRAMINTERFACEIVPROC                       glgenGetProgramInterfaceiv;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC                   glgenGetProgramPipelineInfoLog;
PFNGLGETPROGRAMPIPELINEIVPROC                        glgenGetProgramPipelineiv;
PFNGLGETPROGRAMRESOURCEINDEXPROC                     glgenGetProgramResourceIndex;
PFNGLGETPROGRAMRESOURCELOCATIONPROC                  glgenGetProgramResourceLocation;
PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC             glgenGetProgramResourceLocationIndex;
PFNGLGETPROGRAMRESOURCENAMEPROC                      glgenGetProgramResourceName;
PFNGLGETPROGRAMRESOURCEFVNVPROC                      glgenGetProgramResourcefvNV;
PFNGLGETPROGRAMRESOURCEIVPROC                        glgenGetProgramResourceiv;
PFNGLGETPROGRAMSTAGEIVPROC                           glgenGetProgramStageiv;
PFNGLGETPROGRAMIVPROC                                glgenGetProgramiv;
PFNGLGETQUERYBUFFEROBJECTI64VPROC                    glgenGetQueryBufferObjecti64v;
PFNGLGETQUERYBUFFEROBJECTIVPROC                      glgenGetQueryBufferObjectiv;
PFNGLGETQUERYBUFFEROBJECTUI64VPROC                   glgenGetQueryBufferObjectui64v;
PFNGLGETQUERYBUFFEROBJECTUIVPROC                     glgenGetQueryBufferObjectuiv;
PFNGLGETQUERYINDEXEDIVPROC                           glgenGetQueryIndexediv;
PFNGLGETQUERYOBJECTI64VPROC                          glgenGetQueryObjecti64v;
PFNGLGETQUERYOBJECTIVPROC                            glgenGetQueryObjectiv;
PFNGLGETQUERYOBJECTUI64VPROC                         glgenGetQueryObjectui64v;
PFNGLGETQUERYOBJECTUIVPROC                           glgenGetQueryObjectuiv;
PFNGLGETQUERYIVPROC                                  glgenGetQueryiv;
PFNGLGETRENDERBUFFERPARAMETERIVPROC                  glgenGetRenderbufferParameteriv;
PFNGLGETSAMPLERPARAMETERIIVPROC                      glgenGetSamplerParameterIiv;
PFNGLGETSAMPLERPARAMETERIUIVPROC                     glgenGetSamplerParameterIuiv;
PFNGLGETSAMPLERPARAMETERFVPROC                       glgenGetSamplerParameterfv;
PFNGLGETSAMPLERPARAMETERIVPROC                       glgenGetSamplerParameteriv;
PFNGLGETSHADERINFOLOGPROC                            glgenGetShaderInfoLog;
PFNGLGETSHADERPRECISIONFORMATPROC                    glgenGetShaderPrecisionFormat;
PFNGLGETSHADERSOURCEPROC                             glgenGetShaderSource;
PFNGLGETSHADERIVPROC                                 glgenGetShaderiv;
PFNGLGETSHADINGRATEIMAGEPALETTENVPROC                glgenGetShadingRateImagePaletteNV;
PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC            glgenGetShadingRateSampleLocationivNV;
PFNGLGETSTAGEINDEXNVPROC                             glgenGetStageIndexNV;
PFNGLGETSTRINGPROC                                   glgenGetString;
PFNGLGETSTRINGIPROC                                  glgenGetStringi;
PFNGLGETSUBROUTINEINDEXPROC                          glgenGetSubroutineIndex;
PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC                glgenGetSubroutineUniformLocation;
PFNGLGETSYNCIVPROC                                   glgenGetSynciv;
PFNGLGETTEXIMAGEPROC                                 glgenGetTexImage;
PFNGLGETTEXLEVELPARAMETERFVPROC                      glgenGetTexLevelParameterfv;
PFNGLGETTEXLEVELPARAMETERIVPROC                      glgenGetTexLevelParameteriv;
PFNGLGETTEXPARAMETERIIVPROC                          glgenGetTexParameterIiv;
PFNGLGETTEXPARAMETERIUIVPROC                         glgenGetTexParameterIuiv;
PFNGLGETTEXPARAMETERFVPROC                           glgenGetTexParameterfv;
PFNGLGETTEXPARAMETERIVPROC                           glgenGetTexParameteriv;
PFNGLGETTEXTUREHANDLEARBPROC                         glgenGetTextureHandleARB;
PFNGLGETTEXTUREHANDLENVPROC                          glgenGetTextureHandleNV;
PFNGLGETTEXTUREIMAGEPROC                             glgenGetTextureImage;
PFNGLGETTEXTUREIMAGEEXTPROC                          glgenGetTextureImageEXT;
PFNGLGETTEXTURELEVELPARAMETERFVPROC                  glgenGetTextureLevelParameterfv;
PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC               glgenGetTextureLevelParameterfvEXT;
PFNGLGETTEXTURELEVELPARAMETERIVPROC                  glgenGetTextureLevelParameteriv;
PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC               glgenGetTextureLevelParameterivEXT;
PFNGLGETTEXTUREPARAMETERIIVPROC                      glgenGetTextureParameterIiv;
PFNGLGETTEXTUREPARAMETERIIVEXTPROC                   glgenGetTextureParameterIivEXT;
PFNGLGETTEXTUREPARAMETERIUIVPROC                     glgenGetTextureParameterIuiv;
PFNGLGETTEXTUREPARAMETERIUIVEXTPROC                  glgenGetTextureParameterIuivEXT;
PFNGLGETTEXTUREPARAMETERFVPROC                       glgenGetTextureParameterfv;
PFNGLGETTEXTUREPARAMETERFVEXTPROC                    glgenGetTextureParameterfvEXT;
PFNGLGETTEXTUREPARAMETERIVPROC                       glgenGetTextureParameteriv;
PFNGLGETTEXTUREPARAMETERIVEXTPROC                    glgenGetTextureParameterivEXT;
PFNGLGETTEXTURESAMPLERHANDLEARBPROC                  glgenGetTextureSamplerHandleARB;
PFNGLGETTEXTURESAMPLERHANDLENVPROC                   glgenGetTextureSamplerHandleNV;
PFNGLGETTEXTURESUBIMAGEPROC                          glgenGetTextureSubImage;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC                 glgenGetTransformFeedbackVarying;
PFNGLGETTRANSFORMFEEDBACKI64_VPROC                   glgenGetTransformFeedbacki64_v;
PFNGLGETTRANSFORMFEEDBACKI_VPROC                     glgenGetTransformFeedbacki_v;
PFNGLGETTRANSFORMFEEDBACKIVPROC                      glgenGetTransformFeedbackiv;
PFNGLGETUNIFORMBLOCKINDEXPROC                        glgenGetUniformBlockIndex;
PFNGLGETUNIFORMINDICESPROC                           glgenGetUniformIndices;
PFNGLGETUNIFORMLOCATIONPROC                          glgenGetUniformLocation;
PFNGLGETUNIFORMSUBROUTINEUIVPROC                     glgenGetUniformSubroutineuiv;
PFNGLGETUNIFORMDVPROC                                glgenGetUniformdv;
PFNGLGETUNIFORMFVPROC                                glgenGetUniformfv;
PFNGLGETUNIFORMI64VARBPROC                           glgenGetUniformi64vARB;
PFNGLGETUNIFORMI64VNVPROC                            glgenGetUniformi64vNV;
PFNGLGETUNIFORMIVPROC                                glgenGetUniformiv;
PFNGLGETUNIFORMUI64VARBPROC                          glgenGetUniformui64vARB;
PFNGLGETUNIFORMUI64VNVPROC                           glgenGetUniformui64vNV;
PFNGLGETUNIFORMUIVPROC                               glgenGetUniformuiv;
PFNGLGETVERTEXARRAYINDEXED64IVPROC                   glgenGetVertexArrayIndexed64iv;
PFNGLGETVERTEXARRAYINDEXEDIVPROC                     glgenGetVertexArrayIndexediv;
PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC                 glgenGetVertexArrayIntegeri_vEXT;
PFNGLGETVERTEXARRAYINTEGERVEXTPROC                   glgenGetVertexArrayIntegervEXT;
PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC                 glgenGetVertexArrayPointeri_vEXT;
PFNGLGETVERTEXARRAYPOINTERVEXTPROC                   glgenGetVertexArrayPointervEXT;
PFNGLGETVERTEXARRAYIVPROC                            glgenGetVertexArrayiv;
PFNGLGETVERTEXATTRIBIIVPROC                          glgenGetVertexAttribIiv;
PFNGLGETVERTEXATTRIBIUIVPROC                         glgenGetVertexAttribIuiv;
PFNGLGETVERTEXATTRIBLDVPROC                          glgenGetVertexAttribLdv;
PFNGLGETVERTEXATTRIBLI64VNVPROC                      glgenGetVertexAttribLi64vNV;
PFNGLGETVERTEXATTRIBLUI64VARBPROC                    glgenGetVertexAttribLui64vARB;
PFNGLGETVERTEXATTRIBLUI64VNVPROC                     glgenGetVertexAttribLui64vNV;
PFNGLGETVERTEXATTRIBPOINTERVPROC                     glgenGetVertexAttribPointerv;
PFNGLGETVERTEXATTRIBDVPROC                           glgenGetVertexAttribdv;
PFNGLGETVERTEXATTRIBFVPROC                           glgenGetVertexAttribfv;
PFNGLGETVERTEXATTRIBIVPROC                           glgenGetVertexAttribiv;
PFNGLGETVKPROCADDRNVPROC                             glgenGetVkProcAddrNV;
PFNGLGETNCOMPRESSEDTEXIMAGEPROC                      glgenGetnCompressedTexImage;
PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC                   glgenGetnCompressedTexImageARB;
PFNGLGETNTEXIMAGEPROC                                glgenGetnTexImage;
PFNGLGETNTEXIMAGEARBPROC                             glgenGetnTexImageARB;
PFNGLGETNUNIFORMDVPROC                               glgenGetnUniformdv;
PFNGLGETNUNIFORMDVARBPROC                            glgenGetnUniformdvARB;
PFNGLGETNUNIFORMFVPROC                               glgenGetnUniformfv;
PFNGLGETNUNIFORMFVARBPROC                            glgenGetnUniformfvARB;
PFNGLGETNUNIFORMI64VARBPROC                          glgenGetnUniformi64vARB;
PFNGLGETNUNIFORMIVPROC                               glgenGetnUniformiv;
PFNGLGETNUNIFORMIVARBPROC                            glgenGetnUniformivARB;
PFNGLGETNUNIFORMUI64VARBPROC                         glgenGetnUniformui64vARB;
PFNGLGETNUNIFORMUIVPROC                              glgenGetnUniformuiv;
PFNGLGETNUNIFORMUIVARBPROC                           glgenGetnUniformuivARB;
PFNGLHINTPROC                                        glgenHint;
PFNGLINDEXFORMATNVPROC                               glgenIndexFormatNV;
PFNGLINSERTEVENTMARKEREXTPROC                        glgenInsertEventMarkerEXT;
PFNGLINTERPOLATEPATHSNVPROC                          glgenInterpolatePathsNV;
PFNGLINVALIDATEBUFFERDATAPROC                        glgenInvalidateBufferData;
PFNGLINVALIDATEBUFFERSUBDATAPROC                     glgenInvalidateBufferSubData;
PFNGLINVALIDATEFRAMEBUFFERPROC                       glgenInvalidateFramebuffer;
PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC              glgenInvalidateNamedFramebufferData;
PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC           glgenInvalidateNamedFramebufferSubData;
PFNGLINVALIDATESUBFRAMEBUFFERPROC                    glgenInvalidateSubFramebuffer;
PFNGLINVALIDATETEXIMAGEPROC                          glgenInvalidateTexImage;
PFNGLINVALIDATETEXSUBIMAGEPROC                       glgenInvalidateTexSubImage;
PFNGLISBUFFERPROC                                    glgenIsBuffer;
PFNGLISBUFFERRESIDENTNVPROC                          glgenIsBufferResidentNV;
PFNGLISCOMMANDLISTNVPROC                             glgenIsCommandListNV;
PFNGLISENABLEDPROC                                   glgenIsEnabled;
PFNGLISENABLEDINDEXEDEXTPROC                         glgenIsEnabledIndexedEXT;
PFNGLISENABLEDIPROC                                  glgenIsEnabledi;
PFNGLISFRAMEBUFFERPROC                               glgenIsFramebuffer;
PFNGLISIMAGEHANDLERESIDENTARBPROC                    glgenIsImageHandleResidentARB;
PFNGLISIMAGEHANDLERESIDENTNVPROC                     glgenIsImageHandleResidentNV;
PFNGLISNAMEDBUFFERRESIDENTNVPROC                     glgenIsNamedBufferResidentNV;
PFNGLISNAMEDSTRINGARBPROC                            glgenIsNamedStringARB;
PFNGLISPATHNVPROC                                    glgenIsPathNV;
PFNGLISPOINTINFILLPATHNVPROC                         glgenIsPointInFillPathNV;
PFNGLISPOINTINSTROKEPATHNVPROC                       glgenIsPointInStrokePathNV;
PFNGLISPROGRAMPROC                                   glgenIsProgram;
PFNGLISPROGRAMPIPELINEPROC                           glgenIsProgramPipeline;
PFNGLISQUERYPROC                                     glgenIsQuery;
PFNGLISRENDERBUFFERPROC                              glgenIsRenderbuffer;
PFNGLISSAMPLERPROC                                   glgenIsSampler;
PFNGLISSHADERPROC                                    glgenIsShader;
PFNGLISSTATENVPROC                                   glgenIsStateNV;
PFNGLISSYNCPROC                                      glgenIsSync;
PFNGLISTEXTUREPROC                                   glgenIsTexture;
PFNGLISTEXTUREHANDLERESIDENTARBPROC                  glgenIsTextureHandleResidentARB;
PFNGLISTEXTUREHANDLERESIDENTNVPROC                   glgenIsTextureHandleResidentNV;
PFNGLISTRANSFORMFEEDBACKPROC                         glgenIsTransformFeedback;
PFNGLISVERTEXARRAYPROC                               glgenIsVertexArray;
PFNGLLABELOBJECTEXTPROC                              glgenLabelObjectEXT;
PFNGLLINEWIDTHPROC                                   glgenLineWidth;
PFNGLLINKPROGRAMPROC                                 glgenLinkProgram;
PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC              glgenListDrawCommandsStatesClientNV;
PFNGLLOGICOPPROC                                     glgenLogicOp;
PFNGLMAKEBUFFERNONRESIDENTNVPROC                     glgenMakeBufferNonResidentNV;
PFNGLMAKEBUFFERRESIDENTNVPROC                        glgenMakeBufferResidentNV;
PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC               glgenMakeImageHandleNonResidentARB;
PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC                glgenMakeImageHandleNonResidentNV;
PFNGLMAKEIMAGEHANDLERESIDENTARBPROC                  glgenMakeImageHandleResidentARB;
PFNGLMAKEIMAGEHANDLERESIDENTNVPROC                   glgenMakeImageHandleResidentNV;
PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC                glgenMakeNamedBufferNonResidentNV;
PFNGLMAKENAMEDBUFFERRESIDENTNVPROC                   glgenMakeNamedBufferResidentNV;
PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC             glgenMakeTextureHandleNonResidentARB;
PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC              glgenMakeTextureHandleNonResidentNV;
PFNGLMAKETEXTUREHANDLERESIDENTARBPROC                glgenMakeTextureHandleResidentARB;
PFNGLMAKETEXTUREHANDLERESIDENTNVPROC                 glgenMakeTextureHandleResidentNV;
PFNGLMAPBUFFERPROC                                   glgenMapBuffer;
PFNGLMAPBUFFERRANGEPROC                              glgenMapBufferRange;
PFNGLMAPNAMEDBUFFERPROC                              glgenMapNamedBuffer;
PFNGLMAPNAMEDBUFFEREXTPROC                           glgenMapNamedBufferEXT;
PFNGLMAPNAMEDBUFFERRANGEPROC                         glgenMapNamedBufferRange;
PFNGLMAPNAMEDBUFFERRANGEEXTPROC                      glgenMapNamedBufferRangeEXT;
PFNGLMATRIXFRUSTUMEXTPROC                            glgenMatrixFrustumEXT;
PFNGLMATRIXLOAD3X2FNVPROC                            glgenMatrixLoad3x2fNV;
PFNGLMATRIXLOAD3X3FNVPROC                            glgenMatrixLoad3x3fNV;
PFNGLMATRIXLOADIDENTITYEXTPROC                       glgenMatrixLoadIdentityEXT;
PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC                   glgenMatrixLoadTranspose3x3fNV;
PFNGLMATRIXLOADTRANSPOSEDEXTPROC                     glgenMatrixLoadTransposedEXT;
PFNGLMATRIXLOADTRANSPOSEFEXTPROC                     glgenMatrixLoadTransposefEXT;
PFNGLMATRIXLOADDEXTPROC                              glgenMatrixLoaddEXT;
PFNGLMATRIXLOADFEXTPROC                              glgenMatrixLoadfEXT;
PFNGLMATRIXMULT3X2FNVPROC                            glgenMatrixMult3x2fNV;
PFNGLMATRIXMULT3X3FNVPROC                            glgenMatrixMult3x3fNV;
PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC                   glgenMatrixMultTranspose3x3fNV;
PFNGLMATRIXMULTTRANSPOSEDEXTPROC                     glgenMatrixMultTransposedEXT;
PFNGLMATRIXMULTTRANSPOSEFEXTPROC                     glgenMatrixMultTransposefEXT;
PFNGLMATRIXMULTDEXTPROC                              glgenMatrixMultdEXT;
PFNGLMATRIXMULTFEXTPROC                              glgenMatrixMultfEXT;
PFNGLMATRIXORTHOEXTPROC                              glgenMatrixOrthoEXT;
PFNGLMATRIXPOPEXTPROC                                glgenMatrixPopEXT;
PFNGLMATRIXPUSHEXTPROC                               glgenMatrixPushEXT;
PFNGLMATRIXROTATEDEXTPROC                            glgenMatrixRotatedEXT;
PFNGLMATRIXROTATEFEXTPROC                            glgenMatrixRotatefEXT;
PFNGLMATRIXSCALEDEXTPROC                             glgenMatrixScaledEXT;
PFNGLMATRIXSCALEFEXTPROC                             glgenMatrixScalefEXT;
PFNGLMATRIXTRANSLATEDEXTPROC                         glgenMatrixTranslatedEXT;
PFNGLMATRIXTRANSLATEFEXTPROC                         glgenMatrixTranslatefEXT;
PFNGLMAXSHADERCOMPILERTHREADSARBPROC                 glgenMaxShaderCompilerThreadsARB;
PFNGLMAXSHADERCOMPILERTHREADSKHRPROC                 glgenMaxShaderCompilerThreadsKHR;
PFNGLMEMORYBARRIERPROC                               glgenMemoryBarrier;
PFNGLMEMORYBARRIERBYREGIONPROC                       glgenMemoryBarrierByRegion;
PFNGLMINSAMPLESHADINGPROC                            glgenMinSampleShading;
PFNGLMINSAMPLESHADINGARBPROC                         glgenMinSampleShadingARB;
PFNGLMULTIDRAWARRAYSPROC                             glgenMultiDrawArrays;
PFNGLMULTIDRAWARRAYSINDIRECTPROC                     glgenMultiDrawArraysIndirect;
PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC      glgenMultiDrawArraysIndirectBindlessCountNV;
PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC           glgenMultiDrawArraysIndirectBindlessNV;
PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC                glgenMultiDrawArraysIndirectCount;
PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC             glgenMultiDrawArraysIndirectCountARB;
PFNGLMULTIDRAWELEMENTSPROC                           glgenMultiDrawElements;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC                 glgenMultiDrawElementsBaseVertex;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC                   glgenMultiDrawElementsIndirect;
PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC    glgenMultiDrawElementsIndirectBindlessCountNV;
PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC         glgenMultiDrawElementsIndirectBindlessNV;
PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC              glgenMultiDrawElementsIndirectCount;
PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC           glgenMultiDrawElementsIndirectCountARB;
PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC           glgenMultiDrawMeshTasksIndirectCountNV;
PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC                glgenMultiDrawMeshTasksIndirectNV;
PFNGLMULTITEXBUFFEREXTPROC                           glgenMultiTexBufferEXT;
PFNGLMULTITEXCOORDPOINTEREXTPROC                     glgenMultiTexCoordPointerEXT;
PFNGLMULTITEXENVFEXTPROC                             glgenMultiTexEnvfEXT;
PFNGLMULTITEXENVFVEXTPROC                            glgenMultiTexEnvfvEXT;
PFNGLMULTITEXENVIEXTPROC                             glgenMultiTexEnviEXT;
PFNGLMULTITEXENVIVEXTPROC                            glgenMultiTexEnvivEXT;
PFNGLMULTITEXGENDEXTPROC                             glgenMultiTexGendEXT;
PFNGLMULTITEXGENDVEXTPROC                            glgenMultiTexGendvEXT;
PFNGLMULTITEXGENFEXTPROC                             glgenMultiTexGenfEXT;
PFNGLMULTITEXGENFVEXTPROC                            glgenMultiTexGenfvEXT;
PFNGLMULTITEXGENIEXTPROC                             glgenMultiTexGeniEXT;
PFNGLMULTITEXGENIVEXTPROC                            glgenMultiTexGenivEXT;
PFNGLMULTITEXIMAGE1DEXTPROC                          glgenMultiTexImage1DEXT;
PFNGLMULTITEXIMAGE2DEXTPROC                          glgenMultiTexImage2DEXT;
PFNGLMULTITEXIMAGE3DEXTPROC                          glgenMultiTexImage3DEXT;
PFNGLMULTITEXPARAMETERIIVEXTPROC                     glgenMultiTexParameterIivEXT;
PFNGLMULTITEXPARAMETERIUIVEXTPROC                    glgenMultiTexParameterIuivEXT;
PFNGLMULTITEXPARAMETERFEXTPROC                       glgenMultiTexParameterfEXT;
PFNGLMULTITEXPARAMETERFVEXTPROC                      glgenMultiTexParameterfvEXT;
PFNGLMULTITEXPARAMETERIEXTPROC                       glgenMultiTexParameteriEXT;
PFNGLMULTITEXPARAMETERIVEXTPROC                      glgenMultiTexParameterivEXT;
PFNGLMULTITEXRENDERBUFFEREXTPROC                     glgenMultiTexRenderbufferEXT;
PFNGLMULTITEXSUBIMAGE1DEXTPROC                       glgenMultiTexSubImage1DEXT;
PFNGLMULTITEXSUBIMAGE2DEXTPROC                       glgenMultiTexSubImage2DEXT;
PFNGLMULTITEXSUBIMAGE3DEXTPROC                       glgenMultiTexSubImage3DEXT;
PFNGLNAMEDBUFFERATTACHMEMORYNVPROC                   glgenNamedBufferAttachMemoryNV;
PFNGLNAMEDBUFFERDATAPROC                             glgenNamedBufferData;
PFNGLNAMEDBUFFERDATAEXTPROC                          glgenNamedBufferDataEXT;
PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC                glgenNamedBufferPageCommitmentARB;
PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC                glgenNamedBufferPageCommitmentEXT;
PFNGLNAMEDBUFFERSTORAGEPROC                          glgenNamedBufferStorage;
PFNGLNAMEDBUFFERSTORAGEEXTPROC                       glgenNamedBufferStorageEXT;
PFNGLNAMEDBUFFERSUBDATAPROC                          glgenNamedBufferSubData;
PFNGLNAMEDBUFFERSUBDATAEXTPROC                       glgenNamedBufferSubDataEXT;
PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC                   glgenNamedCopyBufferSubDataEXT;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC                  glgenNamedFramebufferDrawBuffer;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC                 glgenNamedFramebufferDrawBuffers;
PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC                  glgenNamedFramebufferParameteri;
PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC               glgenNamedFramebufferParameteriEXT;
PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC                  glgenNamedFramebufferReadBuffer;
PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC                glgenNamedFramebufferRenderbuffer;
PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC             glgenNamedFramebufferRenderbufferEXT;
PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC        glgenNamedFramebufferSampleLocationsfvARB;
PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC         glgenNamedFramebufferSampleLocationsfvNV;
PFNGLNAMEDFRAMEBUFFERTEXTUREPROC                     glgenNamedFramebufferTexture;
PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC                glgenNamedFramebufferTexture1DEXT;
PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC                glgenNamedFramebufferTexture2DEXT;
PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC                glgenNamedFramebufferTexture3DEXT;
PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC                  glgenNamedFramebufferTextureEXT;
PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC              glgenNamedFramebufferTextureFaceEXT;
PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC                glgenNamedFramebufferTextureLayer;
PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC             glgenNamedFramebufferTextureLayerEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC             glgenNamedProgramLocalParameter4dEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC            glgenNamedProgramLocalParameter4dvEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC             glgenNamedProgramLocalParameter4fEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC            glgenNamedProgramLocalParameter4fvEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC            glgenNamedProgramLocalParameterI4iEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC           glgenNamedProgramLocalParameterI4ivEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC           glgenNamedProgramLocalParameterI4uiEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC          glgenNamedProgramLocalParameterI4uivEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC           glgenNamedProgramLocalParameters4fvEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC          glgenNamedProgramLocalParametersI4ivEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC         glgenNamedProgramLocalParametersI4uivEXT;
PFNGLNAMEDPROGRAMSTRINGEXTPROC                       glgenNamedProgramStringEXT;
PFNGLNAMEDRENDERBUFFERSTORAGEPROC                    glgenNamedRenderbufferStorage;
PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC                 glgenNamedRenderbufferStorageEXT;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC         glgenNamedRenderbufferStorageMultisample;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC glgenNamedRenderbufferStorageMultisampleAdvancedAMD;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC glgenNamedRenderbufferStorageMultisampleCoverageEXT;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC      glgenNamedRenderbufferStorageMultisampleEXT;
PFNGLNAMEDSTRINGARBPROC                              glgenNamedStringARB;
PFNGLNORMALFORMATNVPROC                              glgenNormalFormatNV;
PFNGLOBJECTLABELPROC                                 glgenObjectLabel;
PFNGLOBJECTPTRLABELPROC                              glgenObjectPtrLabel;
PFNGLPATCHPARAMETERFVPROC                            glgenPatchParameterfv;
PFNGLPATCHPARAMETERIPROC                             glgenPatchParameteri;
PFNGLPATHCOMMANDSNVPROC                              glgenPathCommandsNV;
PFNGLPATHCOORDSNVPROC                                glgenPathCoordsNV;
PFNGLPATHCOVERDEPTHFUNCNVPROC                        glgenPathCoverDepthFuncNV;
PFNGLPATHDASHARRAYNVPROC                             glgenPathDashArrayNV;
PFNGLPATHGLYPHINDEXARRAYNVPROC                       glgenPathGlyphIndexArrayNV;
PFNGLPATHGLYPHINDEXRANGENVPROC                       glgenPathGlyphIndexRangeNV;
PFNGLPATHGLYPHRANGENVPROC                            glgenPathGlyphRangeNV;
PFNGLPATHGLYPHSNVPROC                                glgenPathGlyphsNV;
PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC                 glgenPathMemoryGlyphIndexArrayNV;
PFNGLPATHPARAMETERFNVPROC                            glgenPathParameterfNV;
PFNGLPATHPARAMETERFVNVPROC                           glgenPathParameterfvNV;
PFNGLPATHPARAMETERINVPROC                            glgenPathParameteriNV;
PFNGLPATHPARAMETERIVNVPROC                           glgenPathParameterivNV;
PFNGLPATHSTENCILDEPTHOFFSETNVPROC                    glgenPathStencilDepthOffsetNV;
PFNGLPATHSTENCILFUNCNVPROC                           glgenPathStencilFuncNV;
PFNGLPATHSTRINGNVPROC                                glgenPathStringNV;
PFNGLPATHSUBCOMMANDSNVPROC                           glgenPathSubCommandsNV;
PFNGLPATHSUBCOORDSNVPROC                             glgenPathSubCoordsNV;
PFNGLPAUSETRANSFORMFEEDBACKPROC                      glgenPauseTransformFeedback;
PFNGLPIXELSTOREFPROC                                 glgenPixelStoref;
PFNGLPIXELSTOREIPROC                                 glgenPixelStorei;
PFNGLPOINTALONGPATHNVPROC                            glgenPointAlongPathNV;
PFNGLPOINTPARAMETERFPROC                             glgenPointParameterf;
PFNGLPOINTPARAMETERFVPROC                            glgenPointParameterfv;
PFNGLPOINTPARAMETERIPROC                             glgenPointParameteri;
PFNGLPOINTPARAMETERIVPROC                            glgenPointParameteriv;
PFNGLPOINTSIZEPROC                                   glgenPointSize;
PFNGLPOLYGONMODEPROC                                 glgenPolygonMode;
PFNGLPOLYGONOFFSETPROC                               glgenPolygonOffset;
PFNGLPOLYGONOFFSETCLAMPPROC                          glgenPolygonOffsetClamp;
PFNGLPOLYGONOFFSETCLAMPEXTPROC                       glgenPolygonOffsetClampEXT;
PFNGLPOPDEBUGGROUPPROC                               glgenPopDebugGroup;
PFNGLPOPGROUPMARKEREXTPROC                           glgenPopGroupMarkerEXT;
PFNGLPRIMITIVEBOUNDINGBOXARBPROC                     glgenPrimitiveBoundingBoxARB;
PFNGLPRIMITIVERESTARTINDEXPROC                       glgenPrimitiveRestartIndex;
PFNGLPROGRAMBINARYPROC                               glgenProgramBinary;
PFNGLPROGRAMPARAMETERIPROC                           glgenProgramParameteri;
PFNGLPROGRAMPARAMETERIARBPROC                        glgenProgramParameteriARB;
PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC               glgenProgramPathFragmentInputGenNV;
PFNGLPROGRAMUNIFORM1DPROC                            glgenProgramUniform1d;
PFNGLPROGRAMUNIFORM1DEXTPROC                         glgenProgramUniform1dEXT;
PFNGLPROGRAMUNIFORM1DVPROC                           glgenProgramUniform1dv;
PFNGLPROGRAMUNIFORM1DVEXTPROC                        glgenProgramUniform1dvEXT;
PFNGLPROGRAMUNIFORM1FPROC                            glgenProgramUniform1f;
PFNGLPROGRAMUNIFORM1FEXTPROC                         glgenProgramUniform1fEXT;
PFNGLPROGRAMUNIFORM1FVPROC                           glgenProgramUniform1fv;
PFNGLPROGRAMUNIFORM1FVEXTPROC                        glgenProgramUniform1fvEXT;
PFNGLPROGRAMUNIFORM1IPROC                            glgenProgramUniform1i;
PFNGLPROGRAMUNIFORM1I64ARBPROC                       glgenProgramUniform1i64ARB;
PFNGLPROGRAMUNIFORM1I64NVPROC                        glgenProgramUniform1i64NV;
PFNGLPROGRAMUNIFORM1I64VARBPROC                      glgenProgramUniform1i64vARB;
PFNGLPROGRAMUNIFORM1I64VNVPROC                       glgenProgramUniform1i64vNV;
PFNGLPROGRAMUNIFORM1IEXTPROC                         glgenProgramUniform1iEXT;
PFNGLPROGRAMUNIFORM1IVPROC                           glgenProgramUniform1iv;
PFNGLPROGRAMUNIFORM1IVEXTPROC                        glgenProgramUniform1ivEXT;
PFNGLPROGRAMUNIFORM1UIPROC                           glgenProgramUniform1ui;
PFNGLPROGRAMUNIFORM1UI64ARBPROC                      glgenProgramUniform1ui64ARB;
PFNGLPROGRAMUNIFORM1UI64NVPROC                       glgenProgramUniform1ui64NV;
PFNGLPROGRAMUNIFORM1UI64VARBPROC                     glgenProgramUniform1ui64vARB;
PFNGLPROGRAMUNIFORM1UI64VNVPROC                      glgenProgramUniform1ui64vNV;
PFNGLPROGRAMUNIFORM1UIEXTPROC                        glgenProgramUniform1uiEXT;
PFNGLPROGRAMUNIFORM1UIVPROC                          glgenProgramUniform1uiv;
PFNGLPROGRAMUNIFORM1UIVEXTPROC                       glgenProgramUniform1uivEXT;
PFNGLPROGRAMUNIFORM2DPROC                            glgenProgramUniform2d;
PFNGLPROGRAMUNIFORM2DEXTPROC                         glgenProgramUniform2dEXT;
PFNGLPROGRAMUNIFORM2DVPROC                           glgenProgramUniform2dv;
PFNGLPROGRAMUNIFORM2DVEXTPROC                        glgenProgramUniform2dvEXT;
PFNGLPROGRAMUNIFORM2FPROC                            glgenProgramUniform2f;
PFNGLPROGRAMUNIFORM2FEXTPROC                         glgenProgramUniform2fEXT;
PFNGLPROGRAMUNIFORM2FVPROC                           glgenProgramUniform2fv;
PFNGLPROGRAMUNIFORM2FVEXTPROC                        glgenProgramUniform2fvEXT;
PFNGLPROGRAMUNIFORM2IPROC                            glgenProgramUniform2i;
PFNGLPROGRAMUNIFORM2I64ARBPROC                       glgenProgramUniform2i64ARB;
PFNGLPROGRAMUNIFORM2I64NVPROC                        glgenProgramUniform2i64NV;
PFNGLPROGRAMUNIFORM2I64VARBPROC                      glgenProgramUniform2i64vARB;
PFNGLPROGRAMUNIFORM2I64VNVPROC                       glgenProgramUniform2i64vNV;
PFNGLPROGRAMUNIFORM2IEXTPROC                         glgenProgramUniform2iEXT;
PFNGLPROGRAMUNIFORM2IVPROC                           glgenProgramUniform2iv;
PFNGLPROGRAMUNIFORM2IVEXTPROC                        glgenProgramUniform2ivEXT;
PFNGLPROGRAMUNIFORM2UIPROC                           glgenProgramUniform2ui;
PFNGLPROGRAMUNIFORM2UI64ARBPROC                      glgenProgramUniform2ui64ARB;
PFNGLPROGRAMUNIFORM2UI64NVPROC                       glgenProgramUniform2ui64NV;
PFNGLPROGRAMUNIFORM2UI64VARBPROC                     glgenProgramUniform2ui64vARB;
PFNGLPROGRAMUNIFORM2UI64VNVPROC                      glgenProgramUniform2ui64vNV;
PFNGLPROGRAMUNIFORM2UIEXTPROC                        glgenProgramUniform2uiEXT;
PFNGLPROGRAMUNIFORM2UIVPROC                          glgenProgramUniform2uiv;
PFNGLPROGRAMUNIFORM2UIVEXTPROC                       glgenProgramUniform2uivEXT;
PFNGLPROGRAMUNIFORM3DPROC                            glgenProgramUniform3d;
PFNGLPROGRAMUNIFORM3DEXTPROC                         glgenProgramUniform3dEXT;
PFNGLPROGRAMUNIFORM3DVPROC                           glgenProgramUniform3dv;
PFNGLPROGRAMUNIFORM3DVEXTPROC                        glgenProgramUniform3dvEXT;
PFNGLPROGRAMUNIFORM3FPROC                            glgenProgramUniform3f;
PFNGLPROGRAMUNIFORM3FEXTPROC                         glgenProgramUniform3fEXT;
PFNGLPROGRAMUNIFORM3FVPROC                           glgenProgramUniform3fv;
PFNGLPROGRAMUNIFORM3FVEXTPROC                        glgenProgramUniform3fvEXT;
PFNGLPROGRAMUNIFORM3IPROC                            glgenProgramUniform3i;
PFNGLPROGRAMUNIFORM3I64ARBPROC                       glgenProgramUniform3i64ARB;
PFNGLPROGRAMUNIFORM3I64NVPROC                        glgenProgramUniform3i64NV;
PFNGLPROGRAMUNIFORM3I64VARBPROC                      glgenProgramUniform3i64vARB;
PFNGLPROGRAMUNIFORM3I64VNVPROC                       glgenProgramUniform3i64vNV;
PFNGLPROGRAMUNIFORM3IEXTPROC                         glgenProgramUniform3iEXT;
PFNGLPROGRAMUNIFORM3IVPROC                           glgenProgramUniform3iv;
PFNGLPROGRAMUNIFORM3IVEXTPROC                        glgenProgramUniform3ivEXT;
PFNGLPROGRAMUNIFORM3UIPROC                           glgenProgramUniform3ui;
PFNGLPROGRAMUNIFORM3UI64ARBPROC                      glgenProgramUniform3ui64ARB;
PFNGLPROGRAMUNIFORM3UI64NVPROC                       glgenProgramUniform3ui64NV;
PFNGLPROGRAMUNIFORM3UI64VARBPROC                     glgenProgramUniform3ui64vARB;
PFNGLPROGRAMUNIFORM3UI64VNVPROC                      glgenProgramUniform3ui64vNV;
PFNGLPROGRAMUNIFORM3UIEXTPROC                        glgenProgramUniform3uiEXT;
PFNGLPROGRAMUNIFORM3UIVPROC                          glgenProgramUniform3uiv;
PFNGLPROGRAMUNIFORM3UIVEXTPROC                       glgenProgramUniform3uivEXT;
PFNGLPROGRAMUNIFORM4DPROC                            glgenProgramUniform4d;
PFNGLPROGRAMUNIFORM4DEXTPROC                         glgenProgramUniform4dEXT;
PFNGLPROGRAMUNIFORM4DVPROC                           glgenProgramUniform4dv;
PFNGLPROGRAMUNIFORM4DVEXTPROC                        glgenProgramUniform4dvEXT;
PFNGLPROGRAMUNIFORM4FPROC                            glgenProgramUniform4f;
PFNGLPROGRAMUNIFORM4FEXTPROC                         glgenProgramUniform4fEXT;
PFNGLPROGRAMUNIFORM4FVPROC                           glgenProgramUniform4fv;
PFNGLPROGRAMUNIFORM4FVEXTPROC                        glgenProgramUniform4fvEXT;
PFNGLPROGRAMUNIFORM4IPROC                            glgenProgramUniform4i;
PFNGLPROGRAMUNIFORM4I64ARBPROC                       glgenProgramUniform4i64ARB;
PFNGLPROGRAMUNIFORM4I64NVPROC                        glgenProgramUniform4i64NV;
PFNGLPROGRAMUNIFORM4I64VARBPROC                      glgenProgramUniform4i64vARB;
PFNGLPROGRAMUNIFORM4I64VNVPROC                       glgenProgramUniform4i64vNV;
PFNGLPROGRAMUNIFORM4IEXTPROC                         glgenProgramUniform4iEXT;
PFNGLPROGRAMUNIFORM4IVPROC                           glgenProgramUniform4iv;
PFNGLPROGRAMUNIFORM4IVEXTPROC                        glgenProgramUniform4ivEXT;
PFNGLPROGRAMUNIFORM4UIPROC                           glgenProgramUniform4ui;
PFNGLPROGRAMUNIFORM4UI64ARBPROC                      glgenProgramUniform4ui64ARB;
PFNGLPROGRAMUNIFORM4UI64NVPROC                       glgenProgramUniform4ui64NV;
PFNGLPROGRAMUNIFORM4UI64VARBPROC                     glgenProgramUniform4ui64vARB;
PFNGLPROGRAMUNIFORM4UI64VNVPROC                      glgenProgramUniform4ui64vNV;
PFNGLPROGRAMUNIFORM4UIEXTPROC                        glgenProgramUniform4uiEXT;
PFNGLPROGRAMUNIFORM4UIVPROC                          glgenProgramUniform4uiv;
PFNGLPROGRAMUNIFORM4UIVEXTPROC                       glgenProgramUniform4uivEXT;
PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC                 glgenProgramUniformHandleui64ARB;
PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC                  glgenProgramUniformHandleui64NV;
PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC                glgenProgramUniformHandleui64vARB;
PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC                 glgenProgramUniformHandleui64vNV;
PFNGLPROGRAMUNIFORMMATRIX2DVPROC                     glgenProgramUniformMatrix2dv;
PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC                  glgenProgramUniformMatrix2dvEXT;
PFNGLPROGRAMUNIFORMMATRIX2FVPROC                     glgenProgramUniformMatrix2fv;
PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC                  glgenProgramUniformMatrix2fvEXT;
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC                   glgenProgramUniformMatrix2x3dv;
PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC                glgenProgramUniformMatrix2x3dvEXT;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC                   glgenProgramUniformMatrix2x3fv;
PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC                glgenProgramUniformMatrix2x3fvEXT;
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC                   glgenProgramUniformMatrix2x4dv;
PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC                glgenProgramUniformMatrix2x4dvEXT;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC                   glgenProgramUniformMatrix2x4fv;
PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC                glgenProgramUniformMatrix2x4fvEXT;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC                     glgenProgramUniformMatrix3dv;
PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC                  glgenProgramUniformMatrix3dvEXT;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC                     glgenProgramUniformMatrix3fv;
PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC                  glgenProgramUniformMatrix3fvEXT;
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC                   glgenProgramUniformMatrix3x2dv;
PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC                glgenProgramUniformMatrix3x2dvEXT;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC                   glgenProgramUniformMatrix3x2fv;
PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC                glgenProgramUniformMatrix3x2fvEXT;
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC                   glgenProgramUniformMatrix3x4dv;
PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC                glgenProgramUniformMatrix3x4dvEXT;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC                   glgenProgramUniformMatrix3x4fv;
PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC                glgenProgramUniformMatrix3x4fvEXT;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC                     glgenProgramUniformMatrix4dv;
PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC                  glgenProgramUniformMatrix4dvEXT;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC                     glgenProgramUniformMatrix4fv;
PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC                  glgenProgramUniformMatrix4fvEXT;
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC                   glgenProgramUniformMatrix4x2dv;
PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC                glgenProgramUniformMatrix4x2dvEXT;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC                   glgenProgramUniformMatrix4x2fv;
PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC                glgenProgramUniformMatrix4x2fvEXT;
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC                   glgenProgramUniformMatrix4x3dv;
PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC                glgenProgramUniformMatrix4x3dvEXT;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC                   glgenProgramUniformMatrix4x3fv;
PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC                glgenProgramUniformMatrix4x3fvEXT;
PFNGLPROGRAMUNIFORMUI64NVPROC                        glgenProgramUniformui64NV;
PFNGLPROGRAMUNIFORMUI64VNVPROC                       glgenProgramUniformui64vNV;
PFNGLPROVOKINGVERTEXPROC                             glgenProvokingVertex;
PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC                  glgenPushClientAttribDefaultEXT;
PFNGLPUSHDEBUGGROUPPROC                              glgenPushDebugGroup;
PFNGLPUSHGROUPMARKEREXTPROC                          glgenPushGroupMarkerEXT;
PFNGLQUERYCOUNTERPROC                                glgenQueryCounter;
PFNGLRASTERSAMPLESEXTPROC                            glgenRasterSamplesEXT;
PFNGLREADBUFFERPROC                                  glgenReadBuffer;
PFNGLREADPIXELSPROC                                  glgenReadPixels;
PFNGLREADNPIXELSPROC                                 glgenReadnPixels;
PFNGLREADNPIXELSARBPROC                              glgenReadnPixelsARB;
PFNGLRELEASESHADERCOMPILERPROC                       glgenReleaseShaderCompiler;
PFNGLRENDERBUFFERSTORAGEPROC                         glgenRenderbufferStorage;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC              glgenRenderbufferStorageMultisample;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC   glgenRenderbufferStorageMultisampleAdvancedAMD;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC    glgenRenderbufferStorageMultisampleCoverageNV;
PFNGLRESETMEMORYOBJECTPARAMETERNVPROC                glgenResetMemoryObjectParameterNV;
PFNGLRESOLVEDEPTHVALUESNVPROC                        glgenResolveDepthValuesNV;
PFNGLRESUMETRANSFORMFEEDBACKPROC                     glgenResumeTransformFeedback;
PFNGLSAMPLECOVERAGEPROC                              glgenSampleCoverage;
PFNGLSAMPLEMASKIPROC                                 glgenSampleMaski;
PFNGLSAMPLERPARAMETERIIVPROC                         glgenSamplerParameterIiv;
PFNGLSAMPLERPARAMETERIUIVPROC                        glgenSamplerParameterIuiv;
PFNGLSAMPLERPARAMETERFPROC                           glgenSamplerParameterf;
PFNGLSAMPLERPARAMETERFVPROC                          glgenSamplerParameterfv;
PFNGLSAMPLERPARAMETERIPROC                           glgenSamplerParameteri;
PFNGLSAMPLERPARAMETERIVPROC                          glgenSamplerParameteriv;
PFNGLSCISSORPROC                                     glgenScissor;
PFNGLSCISSORARRAYVPROC                               glgenScissorArrayv;
PFNGLSCISSOREXCLUSIVEARRAYVNVPROC                    glgenScissorExclusiveArrayvNV;
PFNGLSCISSOREXCLUSIVENVPROC                          glgenScissorExclusiveNV;
PFNGLSCISSORINDEXEDPROC                              glgenScissorIndexed;
PFNGLSCISSORINDEXEDVPROC                             glgenScissorIndexedv;
PFNGLSECONDARYCOLORFORMATNVPROC                      glgenSecondaryColorFormatNV;
PFNGLSELECTPERFMONITORCOUNTERSAMDPROC                glgenSelectPerfMonitorCountersAMD;
PFNGLSHADERBINARYPROC                                glgenShaderBinary;
PFNGLSHADERSOURCEPROC                                glgenShaderSource;
PFNGLSHADERSTORAGEBLOCKBINDINGPROC                   glgenShaderStorageBlockBinding;
PFNGLSHADINGRATEIMAGEBARRIERNVPROC                   glgenShadingRateImageBarrierNV;
PFNGLSHADINGRATEIMAGEPALETTENVPROC                   glgenShadingRateImagePaletteNV;
PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC              glgenShadingRateSampleOrderCustomNV;
PFNGLSHADINGRATESAMPLEORDERNVPROC                    glgenShadingRateSampleOrderNV;
PFNGLSIGNALVKFENCENVPROC                             glgenSignalVkFenceNV;
PFNGLSIGNALVKSEMAPHORENVPROC                         glgenSignalVkSemaphoreNV;
PFNGLSPECIALIZESHADERPROC                            glgenSpecializeShader;
PFNGLSPECIALIZESHADERARBPROC                         glgenSpecializeShaderARB;
PFNGLSTATECAPTURENVPROC                              glgenStateCaptureNV;
PFNGLSTENCILFILLPATHINSTANCEDNVPROC                  glgenStencilFillPathInstancedNV;
PFNGLSTENCILFILLPATHNVPROC                           glgenStencilFillPathNV;
PFNGLSTENCILFUNCPROC                                 glgenStencilFunc;
PFNGLSTENCILFUNCSEPARATEPROC                         glgenStencilFuncSeparate;
PFNGLSTENCILMASKPROC                                 glgenStencilMask;
PFNGLSTENCILMASKSEPARATEPROC                         glgenStencilMaskSeparate;
PFNGLSTENCILOPPROC                                   glgenStencilOp;
PFNGLSTENCILOPSEPARATEPROC                           glgenStencilOpSeparate;
PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC                glgenStencilStrokePathInstancedNV;
PFNGLSTENCILSTROKEPATHNVPROC                         glgenStencilStrokePathNV;
PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC         glgenStencilThenCoverFillPathInstancedNV;
PFNGLSTENCILTHENCOVERFILLPATHNVPROC                  glgenStencilThenCoverFillPathNV;
PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC       glgenStencilThenCoverStrokePathInstancedNV;
PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC                glgenStencilThenCoverStrokePathNV;
PFNGLSUBPIXELPRECISIONBIASNVPROC                     glgenSubpixelPrecisionBiasNV;
PFNGLTEXATTACHMEMORYNVPROC                           glgenTexAttachMemoryNV;
PFNGLTEXBUFFERPROC                                   glgenTexBuffer;
PFNGLTEXBUFFERARBPROC                                glgenTexBufferARB;
PFNGLTEXBUFFERRANGEPROC                              glgenTexBufferRange;
PFNGLTEXCOORDFORMATNVPROC                            glgenTexCoordFormatNV;
PFNGLTEXIMAGE1DPROC                                  glgenTexImage1D;
PFNGLTEXIMAGE2DPROC                                  glgenTexImage2D;
PFNGLTEXIMAGE2DMULTISAMPLEPROC                       glgenTexImage2DMultisample;
PFNGLTEXIMAGE3DPROC                                  glgenTexImage3D;
PFNGLTEXIMAGE3DMULTISAMPLEPROC                       glgenTexImage3DMultisample;
PFNGLTEXPAGECOMMITMENTARBPROC                        glgenTexPageCommitmentARB;
PFNGLTEXPARAMETERIIVPROC                             glgenTexParameterIiv;
PFNGLTEXPARAMETERIUIVPROC                            glgenTexParameterIuiv;
PFNGLTEXPARAMETERFPROC                               glgenTexParameterf;
PFNGLTEXPARAMETERFVPROC                              glgenTexParameterfv;
PFNGLTEXPARAMETERIPROC                               glgenTexParameteri;
PFNGLTEXPARAMETERIVPROC                              glgenTexParameteriv;
PFNGLTEXSTORAGE1DPROC                                glgenTexStorage1D;
PFNGLTEXSTORAGE2DPROC                                glgenTexStorage2D;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC                     glgenTexStorage2DMultisample;
PFNGLTEXSTORAGE3DPROC                                glgenTexStorage3D;
PFNGLTEXSTORAGE3DMULTISAMPLEPROC                     glgenTexStorage3DMultisample;
PFNGLTEXSUBIMAGE1DPROC                               glgenTexSubImage1D;
PFNGLTEXSUBIMAGE2DPROC                               glgenTexSubImage2D;
PFNGLTEXSUBIMAGE3DPROC                               glgenTexSubImage3D;
PFNGLTEXTUREATTACHMEMORYNVPROC                       glgenTextureAttachMemoryNV;
PFNGLTEXTUREBARRIERPROC                              glgenTextureBarrier;
PFNGLTEXTUREBARRIERNVPROC                            glgenTextureBarrierNV;
PFNGLTEXTUREBUFFERPROC                               glgenTextureBuffer;
PFNGLTEXTUREBUFFEREXTPROC                            glgenTextureBufferEXT;
PFNGLTEXTUREBUFFERRANGEPROC                          glgenTextureBufferRange;
PFNGLTEXTUREBUFFERRANGEEXTPROC                       glgenTextureBufferRangeEXT;
PFNGLTEXTUREIMAGE1DEXTPROC                           glgenTextureImage1DEXT;
PFNGLTEXTUREIMAGE2DEXTPROC                           glgenTextureImage2DEXT;
PFNGLTEXTUREIMAGE3DEXTPROC                           glgenTextureImage3DEXT;
PFNGLTEXTUREPAGECOMMITMENTEXTPROC                    glgenTexturePageCommitmentEXT;
PFNGLTEXTUREPARAMETERIIVPROC                         glgenTextureParameterIiv;
PFNGLTEXTUREPARAMETERIIVEXTPROC                      glgenTextureParameterIivEXT;
PFNGLTEXTUREPARAMETERIUIVPROC                        glgenTextureParameterIuiv;
PFNGLTEXTUREPARAMETERIUIVEXTPROC                     glgenTextureParameterIuivEXT;
PFNGLTEXTUREPARAMETERFPROC                           glgenTextureParameterf;
PFNGLTEXTUREPARAMETERFEXTPROC                        glgenTextureParameterfEXT;
PFNGLTEXTUREPARAMETERFVPROC                          glgenTextureParameterfv;
PFNGLTEXTUREPARAMETERFVEXTPROC                       glgenTextureParameterfvEXT;
PFNGLTEXTUREPARAMETERIPROC                           glgenTextureParameteri;
PFNGLTEXTUREPARAMETERIEXTPROC                        glgenTextureParameteriEXT;
PFNGLTEXTUREPARAMETERIVPROC                          glgenTextureParameteriv;
PFNGLTEXTUREPARAMETERIVEXTPROC                       glgenTextureParameterivEXT;
PFNGLTEXTURERENDERBUFFEREXTPROC                      glgenTextureRenderbufferEXT;
PFNGLTEXTURESTORAGE1DPROC                            glgenTextureStorage1D;
PFNGLTEXTURESTORAGE1DEXTPROC                         glgenTextureStorage1DEXT;
PFNGLTEXTURESTORAGE2DPROC                            glgenTextureStorage2D;
PFNGLTEXTURESTORAGE2DEXTPROC                         glgenTextureStorage2DEXT;
PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC                 glgenTextureStorage2DMultisample;
PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC              glgenTextureStorage2DMultisampleEXT;
PFNGLTEXTURESTORAGE3DPROC                            glgenTextureStorage3D;
PFNGLTEXTURESTORAGE3DEXTPROC                         glgenTextureStorage3DEXT;
PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC                 glgenTextureStorage3DMultisample;
PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC              glgenTextureStorage3DMultisampleEXT;
PFNGLTEXTURESUBIMAGE1DPROC                           glgenTextureSubImage1D;
PFNGLTEXTURESUBIMAGE1DEXTPROC                        glgenTextureSubImage1DEXT;
PFNGLTEXTURESUBIMAGE2DPROC                           glgenTextureSubImage2D;
PFNGLTEXTURESUBIMAGE2DEXTPROC                        glgenTextureSubImage2DEXT;
PFNGLTEXTURESUBIMAGE3DPROC                           glgenTextureSubImage3D;
PFNGLTEXTURESUBIMAGE3DEXTPROC                        glgenTextureSubImage3DEXT;
PFNGLTEXTUREVIEWPROC                                 glgenTextureView;
PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC                 glgenTransformFeedbackBufferBase;
PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC                glgenTransformFeedbackBufferRange;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC                   glgenTransformFeedbackVaryings;
PFNGLTRANSFORMPATHNVPROC                             glgenTransformPathNV;
PFNGLUNIFORM1DPROC                                   glgenUniform1d;
PFNGLUNIFORM1DVPROC                                  glgenUniform1dv;
PFNGLUNIFORM1FPROC                                   glgenUniform1f;
PFNGLUNIFORM1FVPROC                                  glgenUniform1fv;
PFNGLUNIFORM1IPROC                                   glgenUniform1i;
PFNGLUNIFORM1I64ARBPROC                              glgenUniform1i64ARB;
PFNGLUNIFORM1I64NVPROC                               glgenUniform1i64NV;
PFNGLUNIFORM1I64VARBPROC                             glgenUniform1i64vARB;
PFNGLUNIFORM1I64VNVPROC                              glgenUniform1i64vNV;
PFNGLUNIFORM1IVPROC                                  glgenUniform1iv;
PFNGLUNIFORM1UIPROC                                  glgenUniform1ui;
PFNGLUNIFORM1UI64ARBPROC                             glgenUniform1ui64ARB;
PFNGLUNIFORM1UI64NVPROC                              glgenUniform1ui64NV;
PFNGLUNIFORM1UI64VARBPROC                            glgenUniform1ui64vARB;
PFNGLUNIFORM1UI64VNVPROC                             glgenUniform1ui64vNV;
PFNGLUNIFORM1UIVPROC                                 glgenUniform1uiv;
PFNGLUNIFORM2DPROC                                   glgenUniform2d;
PFNGLUNIFORM2DVPROC                                  glgenUniform2dv;
PFNGLUNIFORM2FPROC                                   glgenUniform2f;
PFNGLUNIFORM2FVPROC                                  glgenUniform2fv;
PFNGLUNIFORM2IPROC                                   glgenUniform2i;
PFNGLUNIFORM2I64ARBPROC                              glgenUniform2i64ARB;
PFNGLUNIFORM2I64NVPROC                               glgenUniform2i64NV;
PFNGLUNIFORM2I64VARBPROC                             glgenUniform2i64vARB;
PFNGLUNIFORM2I64VNVPROC                              glgenUniform2i64vNV;
PFNGLUNIFORM2IVPROC                                  glgenUniform2iv;
PFNGLUNIFORM2UIPROC                                  glgenUniform2ui;
PFNGLUNIFORM2UI64ARBPROC                             glgenUniform2ui64ARB;
PFNGLUNIFORM2UI64NVPROC                              glgenUniform2ui64NV;
PFNGLUNIFORM2UI64VARBPROC                            glgenUniform2ui64vARB;
PFNGLUNIFORM2UI64VNVPROC                             glgenUniform2ui64vNV;
PFNGLUNIFORM2UIVPROC                                 glgenUniform2uiv;
PFNGLUNIFORM3DPROC                                   glgenUniform3d;
PFNGLUNIFORM3DVPROC                                  glgenUniform3dv;
PFNGLUNIFORM3FPROC                                   glgenUniform3f;
PFNGLUNIFORM3FVPROC                                  glgenUniform3fv;
PFNGLUNIFORM3IPROC                                   glgenUniform3i;
PFNGLUNIFORM3I64ARBPROC                              glgenUniform3i64ARB;
PFNGLUNIFORM3I64NVPROC                               glgenUniform3i64NV;
PFNGLUNIFORM3I64VARBPROC                             glgenUniform3i64vARB;
PFNGLUNIFORM3I64VNVPROC                              glgenUniform3i64vNV;
PFNGLUNIFORM3IVPROC                                  glgenUniform3iv;
PFNGLUNIFORM3UIPROC                                  glgenUniform3ui;
PFNGLUNIFORM3UI64ARBPROC                             glgenUniform3ui64ARB;
PFNGLUNIFORM3UI64NVPROC                              glgenUniform3ui64NV;
PFNGLUNIFORM3UI64VARBPROC                            glgenUniform3ui64vARB;
PFNGLUNIFORM3UI64VNVPROC                             glgenUniform3ui64vNV;
PFNGLUNIFORM3UIVPROC                                 glgenUniform3uiv;
PFNGLUNIFORM4DPROC                                   glgenUniform4d;
PFNGLUNIFORM4DVPROC                                  glgenUniform4dv;
PFNGLUNIFORM4FPROC                                   glgenUniform4f;
PFNGLUNIFORM4FVPROC                                  glgenUniform4fv;
PFNGLUNIFORM4IPROC                                   glgenUniform4i;
PFNGLUNIFORM4I64ARBPROC                              glgenUniform4i64ARB;
PFNGLUNIFORM4I64NVPROC                               glgenUniform4i64NV;
PFNGLUNIFORM4I64VARBPROC                             glgenUniform4i64vARB;
PFNGLUNIFORM4I64VNVPROC                              glgenUniform4i64vNV;
PFNGLUNIFORM4IVPROC                                  glgenUniform4iv;
PFNGLUNIFORM4UIPROC                                  glgenUniform4ui;
PFNGLUNIFORM4UI64ARBPROC                             glgenUniform4ui64ARB;
PFNGLUNIFORM4UI64NVPROC                              glgenUniform4ui64NV;
PFNGLUNIFORM4UI64VARBPROC                            glgenUniform4ui64vARB;
PFNGLUNIFORM4UI64VNVPROC                             glgenUniform4ui64vNV;
PFNGLUNIFORM4UIVPROC                                 glgenUniform4uiv;
PFNGLUNIFORMBLOCKBINDINGPROC                         glgenUniformBlockBinding;
PFNGLUNIFORMHANDLEUI64ARBPROC                        glgenUniformHandleui64ARB;
PFNGLUNIFORMHANDLEUI64NVPROC                         glgenUniformHandleui64NV;
PFNGLUNIFORMHANDLEUI64VARBPROC                       glgenUniformHandleui64vARB;
PFNGLUNIFORMHANDLEUI64VNVPROC                        glgenUniformHandleui64vNV;
PFNGLUNIFORMMATRIX2DVPROC                            glgenUniformMatrix2dv;
PFNGLUNIFORMMATRIX2FVPROC                            glgenUniformMatrix2fv;
PFNGLUNIFORMMATRIX2X3DVPROC                          glgenUniformMatrix2x3dv;
PFNGLUNIFORMMATRIX2X3FVPROC                          glgenUniformMatrix2x3fv;
PFNGLUNIFORMMATRIX2X4DVPROC                          glgenUniformMatrix2x4dv;
PFNGLUNIFORMMATRIX2X4FVPROC                          glgenUniformMatrix2x4fv;
PFNGLUNIFORMMATRIX3DVPROC                            glgenUniformMatrix3dv;
PFNGLUNIFORMMATRIX3FVPROC                            glgenUniformMatrix3fv;
PFNGLUNIFORMMATRIX3X2DVPROC                          glgenUniformMatrix3x2dv;
PFNGLUNIFORMMATRIX3X2FVPROC                          glgenUniformMatrix3x2fv;
PFNGLUNIFORMMATRIX3X4DVPROC                          glgenUniformMatrix3x4dv;
PFNGLUNIFORMMATRIX3X4FVPROC                          glgenUniformMatrix3x4fv;
PFNGLUNIFORMMATRIX4DVPROC                            glgenUniformMatrix4dv;
PFNGLUNIFORMMATRIX4FVPROC                            glgenUniformMatrix4fv;
PFNGLUNIFORMMATRIX4X2DVPROC                          glgenUniformMatrix4x2dv;
PFNGLUNIFORMMATRIX4X2FVPROC                          glgenUniformMatrix4x2fv;
PFNGLUNIFORMMATRIX4X3DVPROC                          glgenUniformMatrix4x3dv;
PFNGLUNIFORMMATRIX4X3FVPROC                          glgenUniformMatrix4x3fv;
PFNGLUNIFORMSUBROUTINESUIVPROC                       glgenUniformSubroutinesuiv;
PFNGLUNIFORMUI64NVPROC                               glgenUniformui64NV;
PFNGLUNIFORMUI64VNVPROC                              glgenUniformui64vNV;
PFNGLUNMAPBUFFERPROC                                 glgenUnmapBuffer;
PFNGLUNMAPNAMEDBUFFERPROC                            glgenUnmapNamedBuffer;
PFNGLUNMAPNAMEDBUFFEREXTPROC                         glgenUnmapNamedBufferEXT;
PFNGLUSEPROGRAMPROC                                  glgenUseProgram;
PFNGLUSEPROGRAMSTAGESPROC                            glgenUseProgramStages;
PFNGLUSESHADERPROGRAMEXTPROC                         glgenUseShaderProgramEXT;
PFNGLVALIDATEPROGRAMPROC                             glgenValidateProgram;
PFNGLVALIDATEPROGRAMPIPELINEPROC                     glgenValidateProgramPipeline;
PFNGLVERTEXARRAYATTRIBBINDINGPROC                    glgenVertexArrayAttribBinding;
PFNGLVERTEXARRAYATTRIBFORMATPROC                     glgenVertexArrayAttribFormat;
PFNGLVERTEXARRAYATTRIBIFORMATPROC                    glgenVertexArrayAttribIFormat;
PFNGLVERTEXARRAYATTRIBLFORMATPROC                    glgenVertexArrayAttribLFormat;
PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC              glgenVertexArrayBindVertexBufferEXT;
PFNGLVERTEXARRAYBINDINGDIVISORPROC                   glgenVertexArrayBindingDivisor;
PFNGLVERTEXARRAYCOLOROFFSETEXTPROC                   glgenVertexArrayColorOffsetEXT;
PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC                glgenVertexArrayEdgeFlagOffsetEXT;
PFNGLVERTEXARRAYELEMENTBUFFERPROC                    glgenVertexArrayElementBuffer;
PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC                glgenVertexArrayFogCoordOffsetEXT;
PFNGLVERTEXARRAYINDEXOFFSETEXTPROC                   glgenVertexArrayIndexOffsetEXT;
PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC           glgenVertexArrayMultiTexCoordOffsetEXT;
PFNGLVERTEXARRAYNORMALOFFSETEXTPROC                  glgenVertexArrayNormalOffsetEXT;
PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC          glgenVertexArraySecondaryColorOffsetEXT;
PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC                glgenVertexArrayTexCoordOffsetEXT;
PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC           glgenVertexArrayVertexAttribBindingEXT;
PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC           glgenVertexArrayVertexAttribDivisorEXT;
PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC            glgenVertexArrayVertexAttribFormatEXT;
PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC           glgenVertexArrayVertexAttribIFormatEXT;
PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC           glgenVertexArrayVertexAttribIOffsetEXT;
PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC           glgenVertexArrayVertexAttribLFormatEXT;
PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC           glgenVertexArrayVertexAttribLOffsetEXT;
PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC            glgenVertexArrayVertexAttribOffsetEXT;
PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC          glgenVertexArrayVertexBindingDivisorEXT;
PFNGLVERTEXARRAYVERTEXBUFFERPROC                     glgenVertexArrayVertexBuffer;
PFNGLVERTEXARRAYVERTEXBUFFERSPROC                    glgenVertexArrayVertexBuffers;
PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC                  glgenVertexArrayVertexOffsetEXT;
PFNGLVERTEXATTRIB1DPROC                              glgenVertexAttrib1d;
PFNGLVERTEXATTRIB1DVPROC                             glgenVertexAttrib1dv;
PFNGLVERTEXATTRIB1FPROC                              glgenVertexAttrib1f;
PFNGLVERTEXATTRIB1FVPROC                             glgenVertexAttrib1fv;
PFNGLVERTEXATTRIB1SPROC                              glgenVertexAttrib1s;
PFNGLVERTEXATTRIB1SVPROC                             glgenVertexAttrib1sv;
PFNGLVERTEXATTRIB2DPROC                              glgenVertexAttrib2d;
PFNGLVERTEXATTRIB2DVPROC                             glgenVertexAttrib2dv;
PFNGLVERTEXATTRIB2FPROC                              glgenVertexAttrib2f;
PFNGLVERTEXATTRIB2FVPROC                             glgenVertexAttrib2fv;
PFNGLVERTEXATTRIB2SPROC                              glgenVertexAttrib2s;
PFNGLVERTEXATTRIB2SVPROC                             glgenVertexAttrib2sv;
PFNGLVERTEXATTRIB3DPROC                              glgenVertexAttrib3d;
PFNGLVERTEXATTRIB3DVPROC                             glgenVertexAttrib3dv;
PFNGLVERTEXATTRIB3FPROC                              glgenVertexAttrib3f;
PFNGLVERTEXATTRIB3FVPROC                             glgenVertexAttrib3fv;
PFNGLVERTEXATTRIB3SPROC                              glgenVertexAttrib3s;
PFNGLVERTEXATTRIB3SVPROC                             glgenVertexAttrib3sv;
PFNGLVERTEXATTRIB4NBVPROC                            glgenVertexAttrib4Nbv;
PFNGLVERTEXATTRIB4NIVPROC                            glgenVertexAttrib4Niv;
PFNGLVERTEXATTRIB4NSVPROC                            glgenVertexAttrib4Nsv;
PFNGLVERTEXATTRIB4NUBPROC                            glgenVertexAttrib4Nub;
PFNGLVERTEXATTRIB4NUBVPROC                           glgenVertexAttrib4Nubv;
PFNGLVERTEXATTRIB4NUIVPROC                           glgenVertexAttrib4Nuiv;
PFNGLVERTEXATTRIB4NUSVPROC                           glgenVertexAttrib4Nusv;
PFNGLVERTEXATTRIB4BVPROC                             glgenVertexAttrib4bv;
PFNGLVERTEXATTRIB4DPROC                              glgenVertexAttrib4d;
PFNGLVERTEXATTRIB4DVPROC                             glgenVertexAttrib4dv;
PFNGLVERTEXATTRIB4FPROC                              glgenVertexAttrib4f;
PFNGLVERTEXATTRIB4FVPROC                             glgenVertexAttrib4fv;
PFNGLVERTEXATTRIB4IVPROC                             glgenVertexAttrib4iv;
PFNGLVERTEXATTRIB4SPROC                              glgenVertexAttrib4s;
PFNGLVERTEXATTRIB4SVPROC                             glgenVertexAttrib4sv;
PFNGLVERTEXATTRIB4UBVPROC                            glgenVertexAttrib4ubv;
PFNGLVERTEXATTRIB4UIVPROC                            glgenVertexAttrib4uiv;
PFNGLVERTEXATTRIB4USVPROC                            glgenVertexAttrib4usv;
PFNGLVERTEXATTRIBBINDINGPROC                         glgenVertexAttribBinding;
PFNGLVERTEXATTRIBDIVISORPROC                         glgenVertexAttribDivisor;
PFNGLVERTEXATTRIBDIVISORARBPROC                      glgenVertexAttribDivisorARB;
PFNGLVERTEXATTRIBFORMATPROC                          glgenVertexAttribFormat;
PFNGLVERTEXATTRIBFORMATNVPROC                        glgenVertexAttribFormatNV;
PFNGLVERTEXATTRIBI1IPROC                             glgenVertexAttribI1i;
PFNGLVERTEXATTRIBI1IVPROC                            glgenVertexAttribI1iv;
PFNGLVERTEXATTRIBI1UIPROC                            glgenVertexAttribI1ui;
PFNGLVERTEXATTRIBI1UIVPROC                           glgenVertexAttribI1uiv;
PFNGLVERTEXATTRIBI2IPROC                             glgenVertexAttribI2i;
PFNGLVERTEXATTRIBI2IVPROC                            glgenVertexAttribI2iv;
PFNGLVERTEXATTRIBI2UIPROC                            glgenVertexAttribI2ui;
PFNGLVERTEXATTRIBI2UIVPROC                           glgenVertexAttribI2uiv;
PFNGLVERTEXATTRIBI3IPROC                             glgenVertexAttribI3i;
PFNGLVERTEXATTRIBI3IVPROC                            glgenVertexAttribI3iv;
PFNGLVERTEXATTRIBI3UIPROC                            glgenVertexAttribI3ui;
PFNGLVERTEXATTRIBI3UIVPROC                           glgenVertexAttribI3uiv;
PFNGLVERTEXATTRIBI4BVPROC                            glgenVertexAttribI4bv;
PFNGLVERTEXATTRIBI4IPROC                             glgenVertexAttribI4i;
PFNGLVERTEXATTRIBI4IVPROC                            glgenVertexAttribI4iv;
PFNGLVERTEXATTRIBI4SVPROC                            glgenVertexAttribI4sv;
PFNGLVERTEXATTRIBI4UBVPROC                           glgenVertexAttribI4ubv;
PFNGLVERTEXATTRIBI4UIPROC                            glgenVertexAttribI4ui;
PFNGLVERTEXATTRIBI4UIVPROC                           glgenVertexAttribI4uiv;
PFNGLVERTEXATTRIBI4USVPROC                           glgenVertexAttribI4usv;
PFNGLVERTEXATTRIBIFORMATPROC                         glgenVertexAttribIFormat;
PFNGLVERTEXATTRIBIFORMATNVPROC                       glgenVertexAttribIFormatNV;
PFNGLVERTEXATTRIBIPOINTERPROC                        glgenVertexAttribIPointer;
PFNGLVERTEXATTRIBL1DPROC                             glgenVertexAttribL1d;
PFNGLVERTEXATTRIBL1DVPROC                            glgenVertexAttribL1dv;
PFNGLVERTEXATTRIBL1I64NVPROC                         glgenVertexAttribL1i64NV;
PFNGLVERTEXATTRIBL1I64VNVPROC                        glgenVertexAttribL1i64vNV;
PFNGLVERTEXATTRIBL1UI64ARBPROC                       glgenVertexAttribL1ui64ARB;
PFNGLVERTEXATTRIBL1UI64NVPROC                        glgenVertexAttribL1ui64NV;
PFNGLVERTEXATTRIBL1UI64VARBPROC                      glgenVertexAttribL1ui64vARB;
PFNGLVERTEXATTRIBL1UI64VNVPROC                       glgenVertexAttribL1ui64vNV;
PFNGLVERTEXATTRIBL2DPROC                             glgenVertexAttribL2d;
PFNGLVERTEXATTRIBL2DVPROC                            glgenVertexAttribL2dv;
PFNGLVERTEXATTRIBL2I64NVPROC                         glgenVertexAttribL2i64NV;
PFNGLVERTEXATTRIBL2I64VNVPROC                        glgenVertexAttribL2i64vNV;
PFNGLVERTEXATTRIBL2UI64NVPROC                        glgenVertexAttribL2ui64NV;
PFNGLVERTEXATTRIBL2UI64VNVPROC                       glgenVertexAttribL2ui64vNV;
PFNGLVERTEXATTRIBL3DPROC                             glgenVertexAttribL3d;
PFNGLVERTEXATTRIBL3DVPROC                            glgenVertexAttribL3dv;
PFNGLVERTEXATTRIBL3I64NVPROC                         glgenVertexAttribL3i64NV;
PFNGLVERTEXATTRIBL3I64VNVPROC                        glgenVertexAttribL3i64vNV;
PFNGLVERTEXATTRIBL3UI64NVPROC                        glgenVertexAttribL3ui64NV;
PFNGLVERTEXATTRIBL3UI64VNVPROC                       glgenVertexAttribL3ui64vNV;
PFNGLVERTEXATTRIBL4DPROC                             glgenVertexAttribL4d;
PFNGLVERTEXATTRIBL4DVPROC                            glgenVertexAttribL4dv;
PFNGLVERTEXATTRIBL4I64NVPROC                         glgenVertexAttribL4i64NV;
PFNGLVERTEXATTRIBL4I64VNVPROC                        glgenVertexAttribL4i64vNV;
PFNGLVERTEXATTRIBL4UI64NVPROC                        glgenVertexAttribL4ui64NV;
PFNGLVERTEXATTRIBL4UI64VNVPROC                       glgenVertexAttribL4ui64vNV;
PFNGLVERTEXATTRIBLFORMATPROC                         glgenVertexAttribLFormat;
PFNGLVERTEXATTRIBLFORMATNVPROC                       glgenVertexAttribLFormatNV;
PFNGLVERTEXATTRIBLPOINTERPROC                        glgenVertexAttribLPointer;
PFNGLVERTEXATTRIBP1UIPROC                            glgenVertexAttribP1ui;
PFNGLVERTEXATTRIBP1UIVPROC                           glgenVertexAttribP1uiv;
PFNGLVERTEXATTRIBP2UIPROC                            glgenVertexAttribP2ui;
PFNGLVERTEXATTRIBP2UIVPROC                           glgenVertexAttribP2uiv;
PFNGLVERTEXATTRIBP3UIPROC                            glgenVertexAttribP3ui;
PFNGLVERTEXATTRIBP3UIVPROC                           glgenVertexAttribP3uiv;
PFNGLVERTEXATTRIBP4UIPROC                            glgenVertexAttribP4ui;
PFNGLVERTEXATTRIBP4UIVPROC                           glgenVertexAttribP4uiv;
PFNGLVERTEXATTRIBPOINTERPROC                         glgenVertexAttribPointer;
PFNGLVERTEXBINDINGDIVISORPROC                        glgenVertexBindingDivisor;
PFNGLVERTEXFORMATNVPROC                              glgenVertexFormatNV;
PFNGLVIEWPORTPROC                                    glgenViewport;
PFNGLVIEWPORTARRAYVPROC                              glgenViewportArrayv;
PFNGLVIEWPORTINDEXEDFPROC                            glgenViewportIndexedf;
PFNGLVIEWPORTINDEXEDFVPROC                           glgenViewportIndexedfv;
PFNGLVIEWPORTPOSITIONWSCALENVPROC                    glgenViewportPositionWScaleNV;
PFNGLVIEWPORTSWIZZLENVPROC                           glgenViewportSwizzleNV;
PFNGLWAITSYNCPROC                                    glgenWaitSync;
PFNGLWAITVKSEMAPHORENVPROC                           glgenWaitVkSemaphoreNV;
PFNGLWEIGHTPATHSNVPROC                               glgenWeightPathsNV;
PFNGLWINDOWRECTANGLESEXTPROC                         glgenWindowRectanglesEXT;

static void zpl__glgen_load_procs(void)
{
	glgenActiveProgramEXT = (PFNGLACTIVEPROGRAMEXTPROC) zpl__glgen_get_proc("glActiveProgramEXT");
	glgenActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC) zpl__glgen_get_proc("glActiveShaderProgram");
	glgenActiveTexture = (PFNGLACTIVETEXTUREPROC) zpl__glgen_get_proc("glActiveTexture");
	glgenApplyFramebufferAttachmentCMAAINTEL = (PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC) zpl__glgen_get_proc("glApplyFramebufferAttachmentCMAAINTEL");
	glgenAttachShader = (PFNGLATTACHSHADERPROC) zpl__glgen_get_proc("glAttachShader");
	glgenBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC) zpl__glgen_get_proc("glBeginConditionalRender");
	glgenBeginConditionalRenderNV = (PFNGLBEGINCONDITIONALRENDERNVPROC) zpl__glgen_get_proc("glBeginConditionalRenderNV");
	glgenBeginPerfMonitorAMD = (PFNGLBEGINPERFMONITORAMDPROC) zpl__glgen_get_proc("glBeginPerfMonitorAMD");
	glgenBeginPerfQueryINTEL = (PFNGLBEGINPERFQUERYINTELPROC) zpl__glgen_get_proc("glBeginPerfQueryINTEL");
	glgenBeginQuery = (PFNGLBEGINQUERYPROC) zpl__glgen_get_proc("glBeginQuery");
	glgenBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC) zpl__glgen_get_proc("glBeginQueryIndexed");
	glgenBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC) zpl__glgen_get_proc("glBeginTransformFeedback");
	glgenBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) zpl__glgen_get_proc("glBindAttribLocation");
	glgenBindBuffer = (PFNGLBINDBUFFERPROC) zpl__glgen_get_proc("glBindBuffer");
	glgenBindBufferBase = (PFNGLBINDBUFFERBASEPROC) zpl__glgen_get_proc("glBindBufferBase");
	glgenBindBufferRange = (PFNGLBINDBUFFERRANGEPROC) zpl__glgen_get_proc("glBindBufferRange");
	glgenBindBuffersBase = (PFNGLBINDBUFFERSBASEPROC) zpl__glgen_get_proc("glBindBuffersBase");
	glgenBindBuffersRange = (PFNGLBINDBUFFERSRANGEPROC) zpl__glgen_get_proc("glBindBuffersRange");
	glgenBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC) zpl__glgen_get_proc("glBindFragDataLocation");
	glgenBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC) zpl__glgen_get_proc("glBindFragDataLocationIndexed");
	glgenBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) zpl__glgen_get_proc("glBindFramebuffer");
	glgenBindImageTexture = (PFNGLBINDIMAGETEXTUREPROC) zpl__glgen_get_proc("glBindImageTexture");
	glgenBindImageTextures = (PFNGLBINDIMAGETEXTURESPROC) zpl__glgen_get_proc("glBindImageTextures");
	glgenBindMultiTextureEXT = (PFNGLBINDMULTITEXTUREEXTPROC) zpl__glgen_get_proc("glBindMultiTextureEXT");
	glgenBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC) zpl__glgen_get_proc("glBindProgramPipeline");
	glgenBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) zpl__glgen_get_proc("glBindRenderbuffer");
	glgenBindSampler = (PFNGLBINDSAMPLERPROC) zpl__glgen_get_proc("glBindSampler");
	glgenBindSamplers = (PFNGLBINDSAMPLERSPROC) zpl__glgen_get_proc("glBindSamplers");
	glgenBindShadingRateImageNV = (PFNGLBINDSHADINGRATEIMAGENVPROC) zpl__glgen_get_proc("glBindShadingRateImageNV");
	glgenBindTexture = (PFNGLBINDTEXTUREPROC) zpl__glgen_get_proc("glBindTexture");
	glgenBindTextureUnit = (PFNGLBINDTEXTUREUNITPROC) zpl__glgen_get_proc("glBindTextureUnit");
	glgenBindTextures = (PFNGLBINDTEXTURESPROC) zpl__glgen_get_proc("glBindTextures");
	glgenBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC) zpl__glgen_get_proc("glBindTransformFeedback");
	glgenBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) zpl__glgen_get_proc("glBindVertexArray");
	glgenBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC) zpl__glgen_get_proc("glBindVertexBuffer");
	glgenBindVertexBuffers = (PFNGLBINDVERTEXBUFFERSPROC) zpl__glgen_get_proc("glBindVertexBuffers");
	glgenBlendBarrierKHR = (PFNGLBLENDBARRIERKHRPROC) zpl__glgen_get_proc("glBlendBarrierKHR");
	glgenBlendBarrierNV = (PFNGLBLENDBARRIERNVPROC) zpl__glgen_get_proc("glBlendBarrierNV");
	glgenBlendColor = (PFNGLBLENDCOLORPROC) zpl__glgen_get_proc("glBlendColor");
	glgenBlendEquation = (PFNGLBLENDEQUATIONPROC) zpl__glgen_get_proc("glBlendEquation");
	glgenBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC) zpl__glgen_get_proc("glBlendEquationSeparate");
	glgenBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC) zpl__glgen_get_proc("glBlendEquationSeparatei");
	glgenBlendEquationSeparateiARB = (PFNGLBLENDEQUATIONSEPARATEIARBPROC) zpl__glgen_get_proc("glBlendEquationSeparateiARB");
	glgenBlendEquationi = (PFNGLBLENDEQUATIONIPROC) zpl__glgen_get_proc("glBlendEquationi");
	glgenBlendEquationiARB = (PFNGLBLENDEQUATIONIARBPROC) zpl__glgen_get_proc("glBlendEquationiARB");
	glgenBlendFunc = (PFNGLBLENDFUNCPROC) zpl__glgen_get_proc("glBlendFunc");
	glgenBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC) zpl__glgen_get_proc("glBlendFuncSeparate");
	glgenBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC) zpl__glgen_get_proc("glBlendFuncSeparatei");
	glgenBlendFuncSeparateiARB = (PFNGLBLENDFUNCSEPARATEIARBPROC) zpl__glgen_get_proc("glBlendFuncSeparateiARB");
	glgenBlendFunci = (PFNGLBLENDFUNCIPROC) zpl__glgen_get_proc("glBlendFunci");
	glgenBlendFunciARB = (PFNGLBLENDFUNCIARBPROC) zpl__glgen_get_proc("glBlendFunciARB");
	glgenBlendParameteriNV = (PFNGLBLENDPARAMETERINVPROC) zpl__glgen_get_proc("glBlendParameteriNV");
	glgenBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC) zpl__glgen_get_proc("glBlitFramebuffer");
	glgenBlitNamedFramebuffer = (PFNGLBLITNAMEDFRAMEBUFFERPROC) zpl__glgen_get_proc("glBlitNamedFramebuffer");
	glgenBufferAddressRangeNV = (PFNGLBUFFERADDRESSRANGENVPROC) zpl__glgen_get_proc("glBufferAddressRangeNV");
	glgenBufferAttachMemoryNV = (PFNGLBUFFERATTACHMEMORYNVPROC) zpl__glgen_get_proc("glBufferAttachMemoryNV");
	glgenBufferData = (PFNGLBUFFERDATAPROC) zpl__glgen_get_proc("glBufferData");
	glgenBufferPageCommitmentARB = (PFNGLBUFFERPAGECOMMITMENTARBPROC) zpl__glgen_get_proc("glBufferPageCommitmentARB");
	glgenBufferStorage = (PFNGLBUFFERSTORAGEPROC) zpl__glgen_get_proc("glBufferStorage");
	glgenBufferSubData = (PFNGLBUFFERSUBDATAPROC) zpl__glgen_get_proc("glBufferSubData");
	glgenCallCommandListNV = (PFNGLCALLCOMMANDLISTNVPROC) zpl__glgen_get_proc("glCallCommandListNV");
	glgenCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) zpl__glgen_get_proc("glCheckFramebufferStatus");
	glgenCheckNamedFramebufferStatus = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC) zpl__glgen_get_proc("glCheckNamedFramebufferStatus");
	glgenCheckNamedFramebufferStatusEXT = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC) zpl__glgen_get_proc("glCheckNamedFramebufferStatusEXT");
	glgenClampColor = (PFNGLCLAMPCOLORPROC) zpl__glgen_get_proc("glClampColor");
	glgenClear = (PFNGLCLEARPROC) zpl__glgen_get_proc("glClear");
	glgenClearBufferData = (PFNGLCLEARBUFFERDATAPROC) zpl__glgen_get_proc("glClearBufferData");
	glgenClearBufferSubData = (PFNGLCLEARBUFFERSUBDATAPROC) zpl__glgen_get_proc("glClearBufferSubData");
	glgenClearBufferfi = (PFNGLCLEARBUFFERFIPROC) zpl__glgen_get_proc("glClearBufferfi");
	glgenClearBufferfv = (PFNGLCLEARBUFFERFVPROC) zpl__glgen_get_proc("glClearBufferfv");
	glgenClearBufferiv = (PFNGLCLEARBUFFERIVPROC) zpl__glgen_get_proc("glClearBufferiv");
	glgenClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC) zpl__glgen_get_proc("glClearBufferuiv");
	glgenClearColor = (PFNGLCLEARCOLORPROC) zpl__glgen_get_proc("glClearColor");
	glgenClearDepth = (PFNGLCLEARDEPTHPROC) zpl__glgen_get_proc("glClearDepth");
	glgenClearDepthf = (PFNGLCLEARDEPTHFPROC) zpl__glgen_get_proc("glClearDepthf");
	glgenClearNamedBufferData = (PFNGLCLEARNAMEDBUFFERDATAPROC) zpl__glgen_get_proc("glClearNamedBufferData");
	glgenClearNamedBufferDataEXT = (PFNGLCLEARNAMEDBUFFERDATAEXTPROC) zpl__glgen_get_proc("glClearNamedBufferDataEXT");
	glgenClearNamedBufferSubData = (PFNGLCLEARNAMEDBUFFERSUBDATAPROC) zpl__glgen_get_proc("glClearNamedBufferSubData");
	glgenClearNamedBufferSubDataEXT = (PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC) zpl__glgen_get_proc("glClearNamedBufferSubDataEXT");
	glgenClearNamedFramebufferfi = (PFNGLCLEARNAMEDFRAMEBUFFERFIPROC) zpl__glgen_get_proc("glClearNamedFramebufferfi");
	glgenClearNamedFramebufferfv = (PFNGLCLEARNAMEDFRAMEBUFFERFVPROC) zpl__glgen_get_proc("glClearNamedFramebufferfv");
	glgenClearNamedFramebufferiv = (PFNGLCLEARNAMEDFRAMEBUFFERIVPROC) zpl__glgen_get_proc("glClearNamedFramebufferiv");
	glgenClearNamedFramebufferuiv = (PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC) zpl__glgen_get_proc("glClearNamedFramebufferuiv");
	glgenClearStencil = (PFNGLCLEARSTENCILPROC) zpl__glgen_get_proc("glClearStencil");
	glgenClearTexImage = (PFNGLCLEARTEXIMAGEPROC) zpl__glgen_get_proc("glClearTexImage");
	glgenClearTexSubImage = (PFNGLCLEARTEXSUBIMAGEPROC) zpl__glgen_get_proc("glClearTexSubImage");
	glgenClientAttribDefaultEXT = (PFNGLCLIENTATTRIBDEFAULTEXTPROC) zpl__glgen_get_proc("glClientAttribDefaultEXT");
	glgenClientWaitSync = (PFNGLCLIENTWAITSYNCPROC) zpl__glgen_get_proc("glClientWaitSync");
	glgenClipControl = (PFNGLCLIPCONTROLPROC) zpl__glgen_get_proc("glClipControl");
	glgenColorFormatNV = (PFNGLCOLORFORMATNVPROC) zpl__glgen_get_proc("glColorFormatNV");
	glgenColorMask = (PFNGLCOLORMASKPROC) zpl__glgen_get_proc("glColorMask");
	glgenColorMaski = (PFNGLCOLORMASKIPROC) zpl__glgen_get_proc("glColorMaski");
	glgenCommandListSegmentsNV = (PFNGLCOMMANDLISTSEGMENTSNVPROC) zpl__glgen_get_proc("glCommandListSegmentsNV");
	glgenCompileCommandListNV = (PFNGLCOMPILECOMMANDLISTNVPROC) zpl__glgen_get_proc("glCompileCommandListNV");
	glgenCompileShader = (PFNGLCOMPILESHADERPROC) zpl__glgen_get_proc("glCompileShader");
	glgenCompileShaderIncludeARB = (PFNGLCOMPILESHADERINCLUDEARBPROC) zpl__glgen_get_proc("glCompileShaderIncludeARB");
	glgenCompressedMultiTexImage1DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC) zpl__glgen_get_proc("glCompressedMultiTexImage1DEXT");
	glgenCompressedMultiTexImage2DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC) zpl__glgen_get_proc("glCompressedMultiTexImage2DEXT");
	glgenCompressedMultiTexImage3DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC) zpl__glgen_get_proc("glCompressedMultiTexImage3DEXT");
	glgenCompressedMultiTexSubImage1DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC) zpl__glgen_get_proc("glCompressedMultiTexSubImage1DEXT");
	glgenCompressedMultiTexSubImage2DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC) zpl__glgen_get_proc("glCompressedMultiTexSubImage2DEXT");
	glgenCompressedMultiTexSubImage3DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC) zpl__glgen_get_proc("glCompressedMultiTexSubImage3DEXT");
	glgenCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC) zpl__glgen_get_proc("glCompressedTexImage1D");
	glgenCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) zpl__glgen_get_proc("glCompressedTexImage2D");
	glgenCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC) zpl__glgen_get_proc("glCompressedTexImage3D");
	glgenCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) zpl__glgen_get_proc("glCompressedTexSubImage1D");
	glgenCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) zpl__glgen_get_proc("glCompressedTexSubImage2D");
	glgenCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) zpl__glgen_get_proc("glCompressedTexSubImage3D");
	glgenCompressedTextureImage1DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC) zpl__glgen_get_proc("glCompressedTextureImage1DEXT");
	glgenCompressedTextureImage2DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC) zpl__glgen_get_proc("glCompressedTextureImage2DEXT");
	glgenCompressedTextureImage3DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC) zpl__glgen_get_proc("glCompressedTextureImage3DEXT");
	glgenCompressedTextureSubImage1D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC) zpl__glgen_get_proc("glCompressedTextureSubImage1D");
	glgenCompressedTextureSubImage1DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC) zpl__glgen_get_proc("glCompressedTextureSubImage1DEXT");
	glgenCompressedTextureSubImage2D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC) zpl__glgen_get_proc("glCompressedTextureSubImage2D");
	glgenCompressedTextureSubImage2DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC) zpl__glgen_get_proc("glCompressedTextureSubImage2DEXT");
	glgenCompressedTextureSubImage3D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC) zpl__glgen_get_proc("glCompressedTextureSubImage3D");
	glgenCompressedTextureSubImage3DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC) zpl__glgen_get_proc("glCompressedTextureSubImage3DEXT");
	glgenConservativeRasterParameterfNV = (PFNGLCONSERVATIVERASTERPARAMETERFNVPROC) zpl__glgen_get_proc("glConservativeRasterParameterfNV");
	glgenConservativeRasterParameteriNV = (PFNGLCONSERVATIVERASTERPARAMETERINVPROC) zpl__glgen_get_proc("glConservativeRasterParameteriNV");
	glgenCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC) zpl__glgen_get_proc("glCopyBufferSubData");
	glgenCopyImageSubData = (PFNGLCOPYIMAGESUBDATAPROC) zpl__glgen_get_proc("glCopyImageSubData");
	glgenCopyMultiTexImage1DEXT = (PFNGLCOPYMULTITEXIMAGE1DEXTPROC) zpl__glgen_get_proc("glCopyMultiTexImage1DEXT");
	glgenCopyMultiTexImage2DEXT = (PFNGLCOPYMULTITEXIMAGE2DEXTPROC) zpl__glgen_get_proc("glCopyMultiTexImage2DEXT");
	glgenCopyMultiTexSubImage1DEXT = (PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC) zpl__glgen_get_proc("glCopyMultiTexSubImage1DEXT");
	glgenCopyMultiTexSubImage2DEXT = (PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC) zpl__glgen_get_proc("glCopyMultiTexSubImage2DEXT");
	glgenCopyMultiTexSubImage3DEXT = (PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC) zpl__glgen_get_proc("glCopyMultiTexSubImage3DEXT");
	glgenCopyNamedBufferSubData = (PFNGLCOPYNAMEDBUFFERSUBDATAPROC) zpl__glgen_get_proc("glCopyNamedBufferSubData");
	glgenCopyPathNV = (PFNGLCOPYPATHNVPROC) zpl__glgen_get_proc("glCopyPathNV");
	glgenCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC) zpl__glgen_get_proc("glCopyTexImage1D");
	glgenCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC) zpl__glgen_get_proc("glCopyTexImage2D");
	glgenCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC) zpl__glgen_get_proc("glCopyTexSubImage1D");
	glgenCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC) zpl__glgen_get_proc("glCopyTexSubImage2D");
	glgenCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC) zpl__glgen_get_proc("glCopyTexSubImage3D");
	glgenCopyTextureImage1DEXT = (PFNGLCOPYTEXTUREIMAGE1DEXTPROC) zpl__glgen_get_proc("glCopyTextureImage1DEXT");
	glgenCopyTextureImage2DEXT = (PFNGLCOPYTEXTUREIMAGE2DEXTPROC) zpl__glgen_get_proc("glCopyTextureImage2DEXT");
	glgenCopyTextureSubImage1D = (PFNGLCOPYTEXTURESUBIMAGE1DPROC) zpl__glgen_get_proc("glCopyTextureSubImage1D");
	glgenCopyTextureSubImage1DEXT = (PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC) zpl__glgen_get_proc("glCopyTextureSubImage1DEXT");
	glgenCopyTextureSubImage2D = (PFNGLCOPYTEXTURESUBIMAGE2DPROC) zpl__glgen_get_proc("glCopyTextureSubImage2D");
	glgenCopyTextureSubImage2DEXT = (PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC) zpl__glgen_get_proc("glCopyTextureSubImage2DEXT");
	glgenCopyTextureSubImage3D = (PFNGLCOPYTEXTURESUBIMAGE3DPROC) zpl__glgen_get_proc("glCopyTextureSubImage3D");
	glgenCopyTextureSubImage3DEXT = (PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC) zpl__glgen_get_proc("glCopyTextureSubImage3DEXT");
	glgenCoverFillPathInstancedNV = (PFNGLCOVERFILLPATHINSTANCEDNVPROC) zpl__glgen_get_proc("glCoverFillPathInstancedNV");
	glgenCoverFillPathNV = (PFNGLCOVERFILLPATHNVPROC) zpl__glgen_get_proc("glCoverFillPathNV");
	glgenCoverStrokePathInstancedNV = (PFNGLCOVERSTROKEPATHINSTANCEDNVPROC) zpl__glgen_get_proc("glCoverStrokePathInstancedNV");
	glgenCoverStrokePathNV = (PFNGLCOVERSTROKEPATHNVPROC) zpl__glgen_get_proc("glCoverStrokePathNV");
	glgenCoverageModulationNV = (PFNGLCOVERAGEMODULATIONNVPROC) zpl__glgen_get_proc("glCoverageModulationNV");
	glgenCoverageModulationTableNV = (PFNGLCOVERAGEMODULATIONTABLENVPROC) zpl__glgen_get_proc("glCoverageModulationTableNV");
	glgenCreateBuffers = (PFNGLCREATEBUFFERSPROC) zpl__glgen_get_proc("glCreateBuffers");
	glgenCreateCommandListsNV = (PFNGLCREATECOMMANDLISTSNVPROC) zpl__glgen_get_proc("glCreateCommandListsNV");
	glgenCreateFramebuffers = (PFNGLCREATEFRAMEBUFFERSPROC) zpl__glgen_get_proc("glCreateFramebuffers");
	glgenCreatePerfQueryINTEL = (PFNGLCREATEPERFQUERYINTELPROC) zpl__glgen_get_proc("glCreatePerfQueryINTEL");
	glgenCreateProgram = (PFNGLCREATEPROGRAMPROC) zpl__glgen_get_proc("glCreateProgram");
	glgenCreateProgramPipelines = (PFNGLCREATEPROGRAMPIPELINESPROC) zpl__glgen_get_proc("glCreateProgramPipelines");
	glgenCreateQueries = (PFNGLCREATEQUERIESPROC) zpl__glgen_get_proc("glCreateQueries");
	glgenCreateRenderbuffers = (PFNGLCREATERENDERBUFFERSPROC) zpl__glgen_get_proc("glCreateRenderbuffers");
	glgenCreateSamplers = (PFNGLCREATESAMPLERSPROC) zpl__glgen_get_proc("glCreateSamplers");
	glgenCreateShader = (PFNGLCREATESHADERPROC) zpl__glgen_get_proc("glCreateShader");
	glgenCreateShaderProgramEXT = (PFNGLCREATESHADERPROGRAMEXTPROC) zpl__glgen_get_proc("glCreateShaderProgramEXT");
	glgenCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC) zpl__glgen_get_proc("glCreateShaderProgramv");
	glgenCreateStatesNV = (PFNGLCREATESTATESNVPROC) zpl__glgen_get_proc("glCreateStatesNV");
	glgenCreateSyncFromCLeventARB = (PFNGLCREATESYNCFROMCLEVENTARBPROC) zpl__glgen_get_proc("glCreateSyncFromCLeventARB");
	glgenCreateTextures = (PFNGLCREATETEXTURESPROC) zpl__glgen_get_proc("glCreateTextures");
	glgenCreateTransformFeedbacks = (PFNGLCREATETRANSFORMFEEDBACKSPROC) zpl__glgen_get_proc("glCreateTransformFeedbacks");
	glgenCreateVertexArrays = (PFNGLCREATEVERTEXARRAYSPROC) zpl__glgen_get_proc("glCreateVertexArrays");
	glgenCullFace = (PFNGLCULLFACEPROC) zpl__glgen_get_proc("glCullFace");
	glgenDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC) zpl__glgen_get_proc("glDebugMessageCallback");
	glgenDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC) zpl__glgen_get_proc("glDebugMessageCallbackARB");
	glgenDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC) zpl__glgen_get_proc("glDebugMessageControl");
	glgenDebugMessageControlARB = (PFNGLDEBUGMESSAGECONTROLARBPROC) zpl__glgen_get_proc("glDebugMessageControlARB");
	glgenDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC) zpl__glgen_get_proc("glDebugMessageInsert");
	glgenDebugMessageInsertARB = (PFNGLDEBUGMESSAGEINSERTARBPROC) zpl__glgen_get_proc("glDebugMessageInsertARB");
	glgenDeleteBuffers = (PFNGLDELETEBUFFERSPROC) zpl__glgen_get_proc("glDeleteBuffers");
	glgenDeleteCommandListsNV = (PFNGLDELETECOMMANDLISTSNVPROC) zpl__glgen_get_proc("glDeleteCommandListsNV");
	glgenDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) zpl__glgen_get_proc("glDeleteFramebuffers");
	glgenDeleteNamedStringARB = (PFNGLDELETENAMEDSTRINGARBPROC) zpl__glgen_get_proc("glDeleteNamedStringARB");
	glgenDeletePathsNV = (PFNGLDELETEPATHSNVPROC) zpl__glgen_get_proc("glDeletePathsNV");
	glgenDeletePerfMonitorsAMD = (PFNGLDELETEPERFMONITORSAMDPROC) zpl__glgen_get_proc("glDeletePerfMonitorsAMD");
	glgenDeletePerfQueryINTEL = (PFNGLDELETEPERFQUERYINTELPROC) zpl__glgen_get_proc("glDeletePerfQueryINTEL");
	glgenDeleteProgram = (PFNGLDELETEPROGRAMPROC) zpl__glgen_get_proc("glDeleteProgram");
	glgenDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC) zpl__glgen_get_proc("glDeleteProgramPipelines");
	glgenDeleteQueries = (PFNGLDELETEQUERIESPROC) zpl__glgen_get_proc("glDeleteQueries");
	glgenDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) zpl__glgen_get_proc("glDeleteRenderbuffers");
	glgenDeleteSamplers = (PFNGLDELETESAMPLERSPROC) zpl__glgen_get_proc("glDeleteSamplers");
	glgenDeleteShader = (PFNGLDELETESHADERPROC) zpl__glgen_get_proc("glDeleteShader");
	glgenDeleteStatesNV = (PFNGLDELETESTATESNVPROC) zpl__glgen_get_proc("glDeleteStatesNV");
	glgenDeleteSync = (PFNGLDELETESYNCPROC) zpl__glgen_get_proc("glDeleteSync");
	glgenDeleteTextures = (PFNGLDELETETEXTURESPROC) zpl__glgen_get_proc("glDeleteTextures");
	glgenDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC) zpl__glgen_get_proc("glDeleteTransformFeedbacks");
	glgenDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) zpl__glgen_get_proc("glDeleteVertexArrays");
	glgenDepthFunc = (PFNGLDEPTHFUNCPROC) zpl__glgen_get_proc("glDepthFunc");
	glgenDepthMask = (PFNGLDEPTHMASKPROC) zpl__glgen_get_proc("glDepthMask");
	glgenDepthRange = (PFNGLDEPTHRANGEPROC) zpl__glgen_get_proc("glDepthRange");
	glgenDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC) zpl__glgen_get_proc("glDepthRangeArrayv");
	glgenDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC) zpl__glgen_get_proc("glDepthRangeIndexed");
	glgenDepthRangef = (PFNGLDEPTHRANGEFPROC) zpl__glgen_get_proc("glDepthRangef");
	glgenDetachShader = (PFNGLDETACHSHADERPROC) zpl__glgen_get_proc("glDetachShader");
	glgenDisable = (PFNGLDISABLEPROC) zpl__glgen_get_proc("glDisable");
	glgenDisableClientStateIndexedEXT = (PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC) zpl__glgen_get_proc("glDisableClientStateIndexedEXT");
	glgenDisableClientStateiEXT = (PFNGLDISABLECLIENTSTATEIEXTPROC) zpl__glgen_get_proc("glDisableClientStateiEXT");
	glgenDisableIndexedEXT = (PFNGLDISABLEINDEXEDEXTPROC) zpl__glgen_get_proc("glDisableIndexedEXT");
	glgenDisableVertexArrayAttrib = (PFNGLDISABLEVERTEXARRAYATTRIBPROC) zpl__glgen_get_proc("glDisableVertexArrayAttrib");
	glgenDisableVertexArrayAttribEXT = (PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC) zpl__glgen_get_proc("glDisableVertexArrayAttribEXT");
	glgenDisableVertexArrayEXT = (PFNGLDISABLEVERTEXARRAYEXTPROC) zpl__glgen_get_proc("glDisableVertexArrayEXT");
	glgenDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) zpl__glgen_get_proc("glDisableVertexAttribArray");
	glgenDisablei = (PFNGLDISABLEIPROC) zpl__glgen_get_proc("glDisablei");
	glgenDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC) zpl__glgen_get_proc("glDispatchCompute");
	glgenDispatchComputeGroupSizeARB = (PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC) zpl__glgen_get_proc("glDispatchComputeGroupSizeARB");
	glgenDispatchComputeIndirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC) zpl__glgen_get_proc("glDispatchComputeIndirect");
	glgenDrawArrays = (PFNGLDRAWARRAYSPROC) zpl__glgen_get_proc("glDrawArrays");
	glgenDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC) zpl__glgen_get_proc("glDrawArraysIndirect");
	glgenDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC) zpl__glgen_get_proc("glDrawArraysInstanced");
	glgenDrawArraysInstancedARB = (PFNGLDRAWARRAYSINSTANCEDARBPROC) zpl__glgen_get_proc("glDrawArraysInstancedARB");
	glgenDrawArraysInstancedBaseInstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC) zpl__glgen_get_proc("glDrawArraysInstancedBaseInstance");
	glgenDrawArraysInstancedEXT = (PFNGLDRAWARRAYSINSTANCEDEXTPROC) zpl__glgen_get_proc("glDrawArraysInstancedEXT");
	glgenDrawBuffer = (PFNGLDRAWBUFFERPROC) zpl__glgen_get_proc("glDrawBuffer");
	glgenDrawBuffers = (PFNGLDRAWBUFFERSPROC) zpl__glgen_get_proc("glDrawBuffers");
	glgenDrawCommandsAddressNV = (PFNGLDRAWCOMMANDSADDRESSNVPROC) zpl__glgen_get_proc("glDrawCommandsAddressNV");
	glgenDrawCommandsNV = (PFNGLDRAWCOMMANDSNVPROC) zpl__glgen_get_proc("glDrawCommandsNV");
	glgenDrawCommandsStatesAddressNV = (PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC) zpl__glgen_get_proc("glDrawCommandsStatesAddressNV");
	glgenDrawCommandsStatesNV = (PFNGLDRAWCOMMANDSSTATESNVPROC) zpl__glgen_get_proc("glDrawCommandsStatesNV");
	glgenDrawElements = (PFNGLDRAWELEMENTSPROC) zpl__glgen_get_proc("glDrawElements");
	glgenDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC) zpl__glgen_get_proc("glDrawElementsBaseVertex");
	glgenDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC) zpl__glgen_get_proc("glDrawElementsIndirect");
	glgenDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC) zpl__glgen_get_proc("glDrawElementsInstanced");
	glgenDrawElementsInstancedARB = (PFNGLDRAWELEMENTSINSTANCEDARBPROC) zpl__glgen_get_proc("glDrawElementsInstancedARB");
	glgenDrawElementsInstancedBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC) zpl__glgen_get_proc("glDrawElementsInstancedBaseInstance");
	glgenDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) zpl__glgen_get_proc("glDrawElementsInstancedBaseVertex");
	glgenDrawElementsInstancedBaseVertexBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC) zpl__glgen_get_proc("glDrawElementsInstancedBaseVertexBaseInstance");
	glgenDrawElementsInstancedEXT = (PFNGLDRAWELEMENTSINSTANCEDEXTPROC) zpl__glgen_get_proc("glDrawElementsInstancedEXT");
	glgenDrawMeshTasksIndirectNV = (PFNGLDRAWMESHTASKSINDIRECTNVPROC) zpl__glgen_get_proc("glDrawMeshTasksIndirectNV");
	glgenDrawMeshTasksNV = (PFNGLDRAWMESHTASKSNVPROC) zpl__glgen_get_proc("glDrawMeshTasksNV");
	glgenDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) zpl__glgen_get_proc("glDrawRangeElements");
	glgenDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) zpl__glgen_get_proc("glDrawRangeElementsBaseVertex");
	glgenDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC) zpl__glgen_get_proc("glDrawTransformFeedback");
	glgenDrawTransformFeedbackInstanced = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC) zpl__glgen_get_proc("glDrawTransformFeedbackInstanced");
	glgenDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC) zpl__glgen_get_proc("glDrawTransformFeedbackStream");
	glgenDrawTransformFeedbackStreamInstanced = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC) zpl__glgen_get_proc("glDrawTransformFeedbackStreamInstanced");
	glgenDrawVkImageNV = (PFNGLDRAWVKIMAGENVPROC) zpl__glgen_get_proc("glDrawVkImageNV");
	glgenEGLImageTargetTexStorageEXT = (PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC) zpl__glgen_get_proc("glEGLImageTargetTexStorageEXT");
	glgenEGLImageTargetTextureStorageEXT = (PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC) zpl__glgen_get_proc("glEGLImageTargetTextureStorageEXT");
	glgenEdgeFlagFormatNV = (PFNGLEDGEFLAGFORMATNVPROC) zpl__glgen_get_proc("glEdgeFlagFormatNV");
	glgenEnable = (PFNGLENABLEPROC) zpl__glgen_get_proc("glEnable");
	glgenEnableClientStateIndexedEXT = (PFNGLENABLECLIENTSTATEINDEXEDEXTPROC) zpl__glgen_get_proc("glEnableClientStateIndexedEXT");
	glgenEnableClientStateiEXT = (PFNGLENABLECLIENTSTATEIEXTPROC) zpl__glgen_get_proc("glEnableClientStateiEXT");
	glgenEnableIndexedEXT = (PFNGLENABLEINDEXEDEXTPROC) zpl__glgen_get_proc("glEnableIndexedEXT");
	glgenEnableVertexArrayAttrib = (PFNGLENABLEVERTEXARRAYATTRIBPROC) zpl__glgen_get_proc("glEnableVertexArrayAttrib");
	glgenEnableVertexArrayAttribEXT = (PFNGLENABLEVERTEXARRAYATTRIBEXTPROC) zpl__glgen_get_proc("glEnableVertexArrayAttribEXT");
	glgenEnableVertexArrayEXT = (PFNGLENABLEVERTEXARRAYEXTPROC) zpl__glgen_get_proc("glEnableVertexArrayEXT");
	glgenEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) zpl__glgen_get_proc("glEnableVertexAttribArray");
	glgenEnablei = (PFNGLENABLEIPROC) zpl__glgen_get_proc("glEnablei");
	glgenEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC) zpl__glgen_get_proc("glEndConditionalRender");
	glgenEndConditionalRenderNV = (PFNGLENDCONDITIONALRENDERNVPROC) zpl__glgen_get_proc("glEndConditionalRenderNV");
	glgenEndPerfMonitorAMD = (PFNGLENDPERFMONITORAMDPROC) zpl__glgen_get_proc("glEndPerfMonitorAMD");
	glgenEndPerfQueryINTEL = (PFNGLENDPERFQUERYINTELPROC) zpl__glgen_get_proc("glEndPerfQueryINTEL");
	glgenEndQuery = (PFNGLENDQUERYPROC) zpl__glgen_get_proc("glEndQuery");
	glgenEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC) zpl__glgen_get_proc("glEndQueryIndexed");
	glgenEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC) zpl__glgen_get_proc("glEndTransformFeedback");
	glgenEvaluateDepthValuesARB = (PFNGLEVALUATEDEPTHVALUESARBPROC) zpl__glgen_get_proc("glEvaluateDepthValuesARB");
	glgenFenceSync = (PFNGLFENCESYNCPROC) zpl__glgen_get_proc("glFenceSync");
	glgenFinish = (PFNGLFINISHPROC) zpl__glgen_get_proc("glFinish");
	glgenFlush = (PFNGLFLUSHPROC) zpl__glgen_get_proc("glFlush");
	glgenFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC) zpl__glgen_get_proc("glFlushMappedBufferRange");
	glgenFlushMappedNamedBufferRange = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC) zpl__glgen_get_proc("glFlushMappedNamedBufferRange");
	glgenFlushMappedNamedBufferRangeEXT = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC) zpl__glgen_get_proc("glFlushMappedNamedBufferRangeEXT");
	glgenFogCoordFormatNV = (PFNGLFOGCOORDFORMATNVPROC) zpl__glgen_get_proc("glFogCoordFormatNV");
	glgenFragmentCoverageColorNV = (PFNGLFRAGMENTCOVERAGECOLORNVPROC) zpl__glgen_get_proc("glFragmentCoverageColorNV");
	glgenFramebufferDrawBufferEXT = (PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC) zpl__glgen_get_proc("glFramebufferDrawBufferEXT");
	glgenFramebufferDrawBuffersEXT = (PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC) zpl__glgen_get_proc("glFramebufferDrawBuffersEXT");
	glgenFramebufferFetchBarrierEXT = (PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC) zpl__glgen_get_proc("glFramebufferFetchBarrierEXT");
	glgenFramebufferParameteri = (PFNGLFRAMEBUFFERPARAMETERIPROC) zpl__glgen_get_proc("glFramebufferParameteri");
	glgenFramebufferParameteriMESA = (PFNGLFRAMEBUFFERPARAMETERIMESAPROC) zpl__glgen_get_proc("glFramebufferParameteriMESA");
	glgenFramebufferReadBufferEXT = (PFNGLFRAMEBUFFERREADBUFFEREXTPROC) zpl__glgen_get_proc("glFramebufferReadBufferEXT");
	glgenFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) zpl__glgen_get_proc("glFramebufferRenderbuffer");
	glgenFramebufferSampleLocationsfvARB = (PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC) zpl__glgen_get_proc("glFramebufferSampleLocationsfvARB");
	glgenFramebufferSampleLocationsfvNV = (PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) zpl__glgen_get_proc("glFramebufferSampleLocationsfvNV");
	glgenFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC) zpl__glgen_get_proc("glFramebufferTexture");
	glgenFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) zpl__glgen_get_proc("glFramebufferTexture1D");
	glgenFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) zpl__glgen_get_proc("glFramebufferTexture2D");
	glgenFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) zpl__glgen_get_proc("glFramebufferTexture3D");
	glgenFramebufferTextureARB = (PFNGLFRAMEBUFFERTEXTUREARBPROC) zpl__glgen_get_proc("glFramebufferTextureARB");
	glgenFramebufferTextureFaceARB = (PFNGLFRAMEBUFFERTEXTUREFACEARBPROC) zpl__glgen_get_proc("glFramebufferTextureFaceARB");
	glgenFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC) zpl__glgen_get_proc("glFramebufferTextureLayer");
	glgenFramebufferTextureLayerARB = (PFNGLFRAMEBUFFERTEXTURELAYERARBPROC) zpl__glgen_get_proc("glFramebufferTextureLayerARB");
	glgenFramebufferTextureMultiviewOVR = (PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) zpl__glgen_get_proc("glFramebufferTextureMultiviewOVR");
	glgenFrontFace = (PFNGLFRONTFACEPROC) zpl__glgen_get_proc("glFrontFace");
	glgenGenBuffers = (PFNGLGENBUFFERSPROC) zpl__glgen_get_proc("glGenBuffers");
	glgenGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) zpl__glgen_get_proc("glGenFramebuffers");
	glgenGenPathsNV = (PFNGLGENPATHSNVPROC) zpl__glgen_get_proc("glGenPathsNV");
	glgenGenPerfMonitorsAMD = (PFNGLGENPERFMONITORSAMDPROC) zpl__glgen_get_proc("glGenPerfMonitorsAMD");
	glgenGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC) zpl__glgen_get_proc("glGenProgramPipelines");
	glgenGenQueries = (PFNGLGENQUERIESPROC) zpl__glgen_get_proc("glGenQueries");
	glgenGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) zpl__glgen_get_proc("glGenRenderbuffers");
	glgenGenSamplers = (PFNGLGENSAMPLERSPROC) zpl__glgen_get_proc("glGenSamplers");
	glgenGenTextures = (PFNGLGENTEXTURESPROC) zpl__glgen_get_proc("glGenTextures");
	glgenGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC) zpl__glgen_get_proc("glGenTransformFeedbacks");
	glgenGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) zpl__glgen_get_proc("glGenVertexArrays");
	glgenGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) zpl__glgen_get_proc("glGenerateMipmap");
	glgenGenerateMultiTexMipmapEXT = (PFNGLGENERATEMULTITEXMIPMAPEXTPROC) zpl__glgen_get_proc("glGenerateMultiTexMipmapEXT");
	glgenGenerateTextureMipmap = (PFNGLGENERATETEXTUREMIPMAPPROC) zpl__glgen_get_proc("glGenerateTextureMipmap");
	glgenGenerateTextureMipmapEXT = (PFNGLGENERATETEXTUREMIPMAPEXTPROC) zpl__glgen_get_proc("glGenerateTextureMipmapEXT");
	glgenGetActiveAtomicCounterBufferiv = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC) zpl__glgen_get_proc("glGetActiveAtomicCounterBufferiv");
	glgenGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC) zpl__glgen_get_proc("glGetActiveAttrib");
	glgenGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC) zpl__glgen_get_proc("glGetActiveSubroutineName");
	glgenGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC) zpl__glgen_get_proc("glGetActiveSubroutineUniformName");
	glgenGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC) zpl__glgen_get_proc("glGetActiveSubroutineUniformiv");
	glgenGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC) zpl__glgen_get_proc("glGetActiveUniform");
	glgenGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) zpl__glgen_get_proc("glGetActiveUniformBlockName");
	glgenGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC) zpl__glgen_get_proc("glGetActiveUniformBlockiv");
	glgenGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC) zpl__glgen_get_proc("glGetActiveUniformName");
	glgenGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC) zpl__glgen_get_proc("glGetActiveUniformsiv");
	glgenGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC) zpl__glgen_get_proc("glGetAttachedShaders");
	glgenGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) zpl__glgen_get_proc("glGetAttribLocation");
	glgenGetBooleanIndexedvEXT = (PFNGLGETBOOLEANINDEXEDVEXTPROC) zpl__glgen_get_proc("glGetBooleanIndexedvEXT");
	glgenGetBooleani_v = (PFNGLGETBOOLEANI_VPROC) zpl__glgen_get_proc("glGetBooleani_v");
	glgenGetBooleanv = (PFNGLGETBOOLEANVPROC) zpl__glgen_get_proc("glGetBooleanv");
	glgenGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC) zpl__glgen_get_proc("glGetBufferParameteri64v");
	glgenGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) zpl__glgen_get_proc("glGetBufferParameteriv");
	glgenGetBufferParameterui64vNV = (PFNGLGETBUFFERPARAMETERUI64VNVPROC) zpl__glgen_get_proc("glGetBufferParameterui64vNV");
	glgenGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC) zpl__glgen_get_proc("glGetBufferPointerv");
	glgenGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC) zpl__glgen_get_proc("glGetBufferSubData");
	glgenGetCommandHeaderNV = (PFNGLGETCOMMANDHEADERNVPROC) zpl__glgen_get_proc("glGetCommandHeaderNV");
	glgenGetCompressedMultiTexImageEXT = (PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC) zpl__glgen_get_proc("glGetCompressedMultiTexImageEXT");
	glgenGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC) zpl__glgen_get_proc("glGetCompressedTexImage");
	glgenGetCompressedTextureImage = (PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC) zpl__glgen_get_proc("glGetCompressedTextureImage");
	glgenGetCompressedTextureImageEXT = (PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC) zpl__glgen_get_proc("glGetCompressedTextureImageEXT");
	glgenGetCompressedTextureSubImage = (PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC) zpl__glgen_get_proc("glGetCompressedTextureSubImage");
	glgenGetCoverageModulationTableNV = (PFNGLGETCOVERAGEMODULATIONTABLENVPROC) zpl__glgen_get_proc("glGetCoverageModulationTableNV");
	glgenGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC) zpl__glgen_get_proc("glGetDebugMessageLog");
	glgenGetDebugMessageLogARB = (PFNGLGETDEBUGMESSAGELOGARBPROC) zpl__glgen_get_proc("glGetDebugMessageLogARB");
	glgenGetDoubleIndexedvEXT = (PFNGLGETDOUBLEINDEXEDVEXTPROC) zpl__glgen_get_proc("glGetDoubleIndexedvEXT");
	glgenGetDoublei_v = (PFNGLGETDOUBLEI_VPROC) zpl__glgen_get_proc("glGetDoublei_v");
	glgenGetDoublei_vEXT = (PFNGLGETDOUBLEI_VEXTPROC) zpl__glgen_get_proc("glGetDoublei_vEXT");
	glgenGetDoublev = (PFNGLGETDOUBLEVPROC) zpl__glgen_get_proc("glGetDoublev");
	glgenGetError = (PFNGLGETERRORPROC) zpl__glgen_get_proc("glGetError");
	glgenGetFirstPerfQueryIdINTEL = (PFNGLGETFIRSTPERFQUERYIDINTELPROC) zpl__glgen_get_proc("glGetFirstPerfQueryIdINTEL");
	glgenGetFloatIndexedvEXT = (PFNGLGETFLOATINDEXEDVEXTPROC) zpl__glgen_get_proc("glGetFloatIndexedvEXT");
	glgenGetFloati_v = (PFNGLGETFLOATI_VPROC) zpl__glgen_get_proc("glGetFloati_v");
	glgenGetFloati_vEXT = (PFNGLGETFLOATI_VEXTPROC) zpl__glgen_get_proc("glGetFloati_vEXT");
	glgenGetFloatv = (PFNGLGETFLOATVPROC) zpl__glgen_get_proc("glGetFloatv");
	glgenGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC) zpl__glgen_get_proc("glGetFragDataIndex");
	glgenGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC) zpl__glgen_get_proc("glGetFragDataLocation");
	glgenGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) zpl__glgen_get_proc("glGetFramebufferAttachmentParameteriv");
	glgenGetFramebufferParameteriv = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC) zpl__glgen_get_proc("glGetFramebufferParameteriv");
	glgenGetFramebufferParameterivEXT = (PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC) zpl__glgen_get_proc("glGetFramebufferParameterivEXT");
	glgenGetFramebufferParameterivMESA = (PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC) zpl__glgen_get_proc("glGetFramebufferParameterivMESA");
	glgenGetGraphicsResetStatus = (PFNGLGETGRAPHICSRESETSTATUSPROC) zpl__glgen_get_proc("glGetGraphicsResetStatus");
	glgenGetGraphicsResetStatusARB = (PFNGLGETGRAPHICSRESETSTATUSARBPROC) zpl__glgen_get_proc("glGetGraphicsResetStatusARB");
	glgenGetImageHandleARB = (PFNGLGETIMAGEHANDLEARBPROC) zpl__glgen_get_proc("glGetImageHandleARB");
	glgenGetImageHandleNV = (PFNGLGETIMAGEHANDLENVPROC) zpl__glgen_get_proc("glGetImageHandleNV");
	glgenGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC) zpl__glgen_get_proc("glGetInteger64i_v");
	glgenGetInteger64v = (PFNGLGETINTEGER64VPROC) zpl__glgen_get_proc("glGetInteger64v");
	glgenGetIntegerIndexedvEXT = (PFNGLGETINTEGERINDEXEDVEXTPROC) zpl__glgen_get_proc("glGetIntegerIndexedvEXT");
	glgenGetIntegeri_v = (PFNGLGETINTEGERI_VPROC) zpl__glgen_get_proc("glGetIntegeri_v");
	glgenGetIntegerui64i_vNV = (PFNGLGETINTEGERUI64I_VNVPROC) zpl__glgen_get_proc("glGetIntegerui64i_vNV");
	glgenGetIntegerui64vNV = (PFNGLGETINTEGERUI64VNVPROC) zpl__glgen_get_proc("glGetIntegerui64vNV");
	glgenGetIntegerv = (PFNGLGETINTEGERVPROC) zpl__glgen_get_proc("glGetIntegerv");
	glgenGetInternalformatSampleivNV = (PFNGLGETINTERNALFORMATSAMPLEIVNVPROC) zpl__glgen_get_proc("glGetInternalformatSampleivNV");
	glgenGetInternalformati64v = (PFNGLGETINTERNALFORMATI64VPROC) zpl__glgen_get_proc("glGetInternalformati64v");
	glgenGetInternalformativ = (PFNGLGETINTERNALFORMATIVPROC) zpl__glgen_get_proc("glGetInternalformativ");
	glgenGetMemoryObjectDetachedResourcesuivNV = (PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC) zpl__glgen_get_proc("glGetMemoryObjectDetachedResourcesuivNV");
	glgenGetMultiTexEnvfvEXT = (PFNGLGETMULTITEXENVFVEXTPROC) zpl__glgen_get_proc("glGetMultiTexEnvfvEXT");
	glgenGetMultiTexEnvivEXT = (PFNGLGETMULTITEXENVIVEXTPROC) zpl__glgen_get_proc("glGetMultiTexEnvivEXT");
	glgenGetMultiTexGendvEXT = (PFNGLGETMULTITEXGENDVEXTPROC) zpl__glgen_get_proc("glGetMultiTexGendvEXT");
	glgenGetMultiTexGenfvEXT = (PFNGLGETMULTITEXGENFVEXTPROC) zpl__glgen_get_proc("glGetMultiTexGenfvEXT");
	glgenGetMultiTexGenivEXT = (PFNGLGETMULTITEXGENIVEXTPROC) zpl__glgen_get_proc("glGetMultiTexGenivEXT");
	glgenGetMultiTexImageEXT = (PFNGLGETMULTITEXIMAGEEXTPROC) zpl__glgen_get_proc("glGetMultiTexImageEXT");
	glgenGetMultiTexLevelParameterfvEXT = (PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC) zpl__glgen_get_proc("glGetMultiTexLevelParameterfvEXT");
	glgenGetMultiTexLevelParameterivEXT = (PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC) zpl__glgen_get_proc("glGetMultiTexLevelParameterivEXT");
	glgenGetMultiTexParameterIivEXT = (PFNGLGETMULTITEXPARAMETERIIVEXTPROC) zpl__glgen_get_proc("glGetMultiTexParameterIivEXT");
	glgenGetMultiTexParameterIuivEXT = (PFNGLGETMULTITEXPARAMETERIUIVEXTPROC) zpl__glgen_get_proc("glGetMultiTexParameterIuivEXT");
	glgenGetMultiTexParameterfvEXT = (PFNGLGETMULTITEXPARAMETERFVEXTPROC) zpl__glgen_get_proc("glGetMultiTexParameterfvEXT");
	glgenGetMultiTexParameterivEXT = (PFNGLGETMULTITEXPARAMETERIVEXTPROC) zpl__glgen_get_proc("glGetMultiTexParameterivEXT");
	glgenGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC) zpl__glgen_get_proc("glGetMultisamplefv");
	glgenGetNamedBufferParameteri64v = (PFNGLGETNAMEDBUFFERPARAMETERI64VPROC) zpl__glgen_get_proc("glGetNamedBufferParameteri64v");
	glgenGetNamedBufferParameteriv = (PFNGLGETNAMEDBUFFERPARAMETERIVPROC) zpl__glgen_get_proc("glGetNamedBufferParameteriv");
	glgenGetNamedBufferParameterivEXT = (PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC) zpl__glgen_get_proc("glGetNamedBufferParameterivEXT");
	glgenGetNamedBufferParameterui64vNV = (PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC) zpl__glgen_get_proc("glGetNamedBufferParameterui64vNV");
	glgenGetNamedBufferPointerv = (PFNGLGETNAMEDBUFFERPOINTERVPROC) zpl__glgen_get_proc("glGetNamedBufferPointerv");
	glgenGetNamedBufferPointervEXT = (PFNGLGETNAMEDBUFFERPOINTERVEXTPROC) zpl__glgen_get_proc("glGetNamedBufferPointervEXT");
	glgenGetNamedBufferSubData = (PFNGLGETNAMEDBUFFERSUBDATAPROC) zpl__glgen_get_proc("glGetNamedBufferSubData");
	glgenGetNamedBufferSubDataEXT = (PFNGLGETNAMEDBUFFERSUBDATAEXTPROC) zpl__glgen_get_proc("glGetNamedBufferSubDataEXT");
	glgenGetNamedFramebufferAttachmentParameteriv = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC) zpl__glgen_get_proc("glGetNamedFramebufferAttachmentParameteriv");
	glgenGetNamedFramebufferAttachmentParameterivEXT = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) zpl__glgen_get_proc("glGetNamedFramebufferAttachmentParameterivEXT");
	glgenGetNamedFramebufferParameteriv = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC) zpl__glgen_get_proc("glGetNamedFramebufferParameteriv");
	glgenGetNamedFramebufferParameterivEXT = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC) zpl__glgen_get_proc("glGetNamedFramebufferParameterivEXT");
	glgenGetNamedProgramLocalParameterIivEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC) zpl__glgen_get_proc("glGetNamedProgramLocalParameterIivEXT");
	glgenGetNamedProgramLocalParameterIuivEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC) zpl__glgen_get_proc("glGetNamedProgramLocalParameterIuivEXT");
	glgenGetNamedProgramLocalParameterdvEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC) zpl__glgen_get_proc("glGetNamedProgramLocalParameterdvEXT");
	glgenGetNamedProgramLocalParameterfvEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC) zpl__glgen_get_proc("glGetNamedProgramLocalParameterfvEXT");
	glgenGetNamedProgramStringEXT = (PFNGLGETNAMEDPROGRAMSTRINGEXTPROC) zpl__glgen_get_proc("glGetNamedProgramStringEXT");
	glgenGetNamedProgramivEXT = (PFNGLGETNAMEDPROGRAMIVEXTPROC) zpl__glgen_get_proc("glGetNamedProgramivEXT");
	glgenGetNamedRenderbufferParameteriv = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC) zpl__glgen_get_proc("glGetNamedRenderbufferParameteriv");
	glgenGetNamedRenderbufferParameterivEXT = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC) zpl__glgen_get_proc("glGetNamedRenderbufferParameterivEXT");
	glgenGetNamedStringARB = (PFNGLGETNAMEDSTRINGARBPROC) zpl__glgen_get_proc("glGetNamedStringARB");
	glgenGetNamedStringivARB = (PFNGLGETNAMEDSTRINGIVARBPROC) zpl__glgen_get_proc("glGetNamedStringivARB");
	glgenGetNextPerfQueryIdINTEL = (PFNGLGETNEXTPERFQUERYIDINTELPROC) zpl__glgen_get_proc("glGetNextPerfQueryIdINTEL");
	glgenGetObjectLabel = (PFNGLGETOBJECTLABELPROC) zpl__glgen_get_proc("glGetObjectLabel");
	glgenGetObjectLabelEXT = (PFNGLGETOBJECTLABELEXTPROC) zpl__glgen_get_proc("glGetObjectLabelEXT");
	glgenGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC) zpl__glgen_get_proc("glGetObjectPtrLabel");
	glgenGetPathCommandsNV = (PFNGLGETPATHCOMMANDSNVPROC) zpl__glgen_get_proc("glGetPathCommandsNV");
	glgenGetPathCoordsNV = (PFNGLGETPATHCOORDSNVPROC) zpl__glgen_get_proc("glGetPathCoordsNV");
	glgenGetPathDashArrayNV = (PFNGLGETPATHDASHARRAYNVPROC) zpl__glgen_get_proc("glGetPathDashArrayNV");
	glgenGetPathLengthNV = (PFNGLGETPATHLENGTHNVPROC) zpl__glgen_get_proc("glGetPathLengthNV");
	glgenGetPathMetricRangeNV = (PFNGLGETPATHMETRICRANGENVPROC) zpl__glgen_get_proc("glGetPathMetricRangeNV");
	glgenGetPathMetricsNV = (PFNGLGETPATHMETRICSNVPROC) zpl__glgen_get_proc("glGetPathMetricsNV");
	glgenGetPathParameterfvNV = (PFNGLGETPATHPARAMETERFVNVPROC) zpl__glgen_get_proc("glGetPathParameterfvNV");
	glgenGetPathParameterivNV = (PFNGLGETPATHPARAMETERIVNVPROC) zpl__glgen_get_proc("glGetPathParameterivNV");
	glgenGetPathSpacingNV = (PFNGLGETPATHSPACINGNVPROC) zpl__glgen_get_proc("glGetPathSpacingNV");
	glgenGetPerfCounterInfoINTEL = (PFNGLGETPERFCOUNTERINFOINTELPROC) zpl__glgen_get_proc("glGetPerfCounterInfoINTEL");
	glgenGetPerfMonitorCounterDataAMD = (PFNGLGETPERFMONITORCOUNTERDATAAMDPROC) zpl__glgen_get_proc("glGetPerfMonitorCounterDataAMD");
	glgenGetPerfMonitorCounterInfoAMD = (PFNGLGETPERFMONITORCOUNTERINFOAMDPROC) zpl__glgen_get_proc("glGetPerfMonitorCounterInfoAMD");
	glgenGetPerfMonitorCounterStringAMD = (PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC) zpl__glgen_get_proc("glGetPerfMonitorCounterStringAMD");
	glgenGetPerfMonitorCountersAMD = (PFNGLGETPERFMONITORCOUNTERSAMDPROC) zpl__glgen_get_proc("glGetPerfMonitorCountersAMD");
	glgenGetPerfMonitorGroupStringAMD = (PFNGLGETPERFMONITORGROUPSTRINGAMDPROC) zpl__glgen_get_proc("glGetPerfMonitorGroupStringAMD");
	glgenGetPerfMonitorGroupsAMD = (PFNGLGETPERFMONITORGROUPSAMDPROC) zpl__glgen_get_proc("glGetPerfMonitorGroupsAMD");
	glgenGetPerfQueryDataINTEL = (PFNGLGETPERFQUERYDATAINTELPROC) zpl__glgen_get_proc("glGetPerfQueryDataINTEL");
	glgenGetPerfQueryIdByNameINTEL = (PFNGLGETPERFQUERYIDBYNAMEINTELPROC) zpl__glgen_get_proc("glGetPerfQueryIdByNameINTEL");
	glgenGetPerfQueryInfoINTEL = (PFNGLGETPERFQUERYINFOINTELPROC) zpl__glgen_get_proc("glGetPerfQueryInfoINTEL");
	glgenGetPointerIndexedvEXT = (PFNGLGETPOINTERINDEXEDVEXTPROC) zpl__glgen_get_proc("glGetPointerIndexedvEXT");
	glgenGetPointeri_vEXT = (PFNGLGETPOINTERI_VEXTPROC) zpl__glgen_get_proc("glGetPointeri_vEXT");
	glgenGetPointerv = (PFNGLGETPOINTERVPROC) zpl__glgen_get_proc("glGetPointerv");
	glgenGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC) zpl__glgen_get_proc("glGetProgramBinary");
	glgenGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) zpl__glgen_get_proc("glGetProgramInfoLog");
	glgenGetProgramInterfaceiv = (PFNGLGETPROGRAMINTERFACEIVPROC) zpl__glgen_get_proc("glGetProgramInterfaceiv");
	glgenGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC) zpl__glgen_get_proc("glGetProgramPipelineInfoLog");
	glgenGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC) zpl__glgen_get_proc("glGetProgramPipelineiv");
	glgenGetProgramResourceIndex = (PFNGLGETPROGRAMRESOURCEINDEXPROC) zpl__glgen_get_proc("glGetProgramResourceIndex");
	glgenGetProgramResourceLocation = (PFNGLGETPROGRAMRESOURCELOCATIONPROC) zpl__glgen_get_proc("glGetProgramResourceLocation");
	glgenGetProgramResourceLocationIndex = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC) zpl__glgen_get_proc("glGetProgramResourceLocationIndex");
	glgenGetProgramResourceName = (PFNGLGETPROGRAMRESOURCENAMEPROC) zpl__glgen_get_proc("glGetProgramResourceName");
	glgenGetProgramResourcefvNV = (PFNGLGETPROGRAMRESOURCEFVNVPROC) zpl__glgen_get_proc("glGetProgramResourcefvNV");
	glgenGetProgramResourceiv = (PFNGLGETPROGRAMRESOURCEIVPROC) zpl__glgen_get_proc("glGetProgramResourceiv");
	glgenGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC) zpl__glgen_get_proc("glGetProgramStageiv");
	glgenGetProgramiv = (PFNGLGETPROGRAMIVPROC) zpl__glgen_get_proc("glGetProgramiv");
	glgenGetQueryBufferObjecti64v = (PFNGLGETQUERYBUFFEROBJECTI64VPROC) zpl__glgen_get_proc("glGetQueryBufferObjecti64v");
	glgenGetQueryBufferObjectiv = (PFNGLGETQUERYBUFFEROBJECTIVPROC) zpl__glgen_get_proc("glGetQueryBufferObjectiv");
	glgenGetQueryBufferObjectui64v = (PFNGLGETQUERYBUFFEROBJECTUI64VPROC) zpl__glgen_get_proc("glGetQueryBufferObjectui64v");
	glgenGetQueryBufferObjectuiv = (PFNGLGETQUERYBUFFEROBJECTUIVPROC) zpl__glgen_get_proc("glGetQueryBufferObjectuiv");
	glgenGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC) zpl__glgen_get_proc("glGetQueryIndexediv");
	glgenGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC) zpl__glgen_get_proc("glGetQueryObjecti64v");
	glgenGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC) zpl__glgen_get_proc("glGetQueryObjectiv");
	glgenGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC) zpl__glgen_get_proc("glGetQueryObjectui64v");
	glgenGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC) zpl__glgen_get_proc("glGetQueryObjectuiv");
	glgenGetQueryiv = (PFNGLGETQUERYIVPROC) zpl__glgen_get_proc("glGetQueryiv");
	glgenGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) zpl__glgen_get_proc("glGetRenderbufferParameteriv");
	glgenGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC) zpl__glgen_get_proc("glGetSamplerParameterIiv");
	glgenGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC) zpl__glgen_get_proc("glGetSamplerParameterIuiv");
	glgenGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC) zpl__glgen_get_proc("glGetSamplerParameterfv");
	glgenGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC) zpl__glgen_get_proc("glGetSamplerParameteriv");
	glgenGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) zpl__glgen_get_proc("glGetShaderInfoLog");
	glgenGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC) zpl__glgen_get_proc("glGetShaderPrecisionFormat");
	glgenGetShaderSource = (PFNGLGETSHADERSOURCEPROC) zpl__glgen_get_proc("glGetShaderSource");
	glgenGetShaderiv = (PFNGLGETSHADERIVPROC) zpl__glgen_get_proc("glGetShaderiv");
	glgenGetShadingRateImagePaletteNV = (PFNGLGETSHADINGRATEIMAGEPALETTENVPROC) zpl__glgen_get_proc("glGetShadingRateImagePaletteNV");
	glgenGetShadingRateSampleLocationivNV = (PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC) zpl__glgen_get_proc("glGetShadingRateSampleLocationivNV");
	glgenGetStageIndexNV = (PFNGLGETSTAGEINDEXNVPROC) zpl__glgen_get_proc("glGetStageIndexNV");
	glgenGetString = (PFNGLGETSTRINGPROC) zpl__glgen_get_proc("glGetString");
	glgenGetStringi = (PFNGLGETSTRINGIPROC) zpl__glgen_get_proc("glGetStringi");
	glgenGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC) zpl__glgen_get_proc("glGetSubroutineIndex");
	glgenGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC) zpl__glgen_get_proc("glGetSubroutineUniformLocation");
	glgenGetSynciv = (PFNGLGETSYNCIVPROC) zpl__glgen_get_proc("glGetSynciv");
	glgenGetTexImage = (PFNGLGETTEXIMAGEPROC) zpl__glgen_get_proc("glGetTexImage");
	glgenGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC) zpl__glgen_get_proc("glGetTexLevelParameterfv");
	glgenGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC) zpl__glgen_get_proc("glGetTexLevelParameteriv");
	glgenGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC) zpl__glgen_get_proc("glGetTexParameterIiv");
	glgenGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC) zpl__glgen_get_proc("glGetTexParameterIuiv");
	glgenGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC) zpl__glgen_get_proc("glGetTexParameterfv");
	glgenGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC) zpl__glgen_get_proc("glGetTexParameteriv");
	glgenGetTextureHandleARB = (PFNGLGETTEXTUREHANDLEARBPROC) zpl__glgen_get_proc("glGetTextureHandleARB");
	glgenGetTextureHandleNV = (PFNGLGETTEXTUREHANDLENVPROC) zpl__glgen_get_proc("glGetTextureHandleNV");
	glgenGetTextureImage = (PFNGLGETTEXTUREIMAGEPROC) zpl__glgen_get_proc("glGetTextureImage");
	glgenGetTextureImageEXT = (PFNGLGETTEXTUREIMAGEEXTPROC) zpl__glgen_get_proc("glGetTextureImageEXT");
	glgenGetTextureLevelParameterfv = (PFNGLGETTEXTURELEVELPARAMETERFVPROC) zpl__glgen_get_proc("glGetTextureLevelParameterfv");
	glgenGetTextureLevelParameterfvEXT = (PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC) zpl__glgen_get_proc("glGetTextureLevelParameterfvEXT");
	glgenGetTextureLevelParameteriv = (PFNGLGETTEXTURELEVELPARAMETERIVPROC) zpl__glgen_get_proc("glGetTextureLevelParameteriv");
	glgenGetTextureLevelParameterivEXT = (PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC) zpl__glgen_get_proc("glGetTextureLevelParameterivEXT");
	glgenGetTextureParameterIiv = (PFNGLGETTEXTUREPARAMETERIIVPROC) zpl__glgen_get_proc("glGetTextureParameterIiv");
	glgenGetTextureParameterIivEXT = (PFNGLGETTEXTUREPARAMETERIIVEXTPROC) zpl__glgen_get_proc("glGetTextureParameterIivEXT");
	glgenGetTextureParameterIuiv = (PFNGLGETTEXTUREPARAMETERIUIVPROC) zpl__glgen_get_proc("glGetTextureParameterIuiv");
	glgenGetTextureParameterIuivEXT = (PFNGLGETTEXTUREPARAMETERIUIVEXTPROC) zpl__glgen_get_proc("glGetTextureParameterIuivEXT");
	glgenGetTextureParameterfv = (PFNGLGETTEXTUREPARAMETERFVPROC) zpl__glgen_get_proc("glGetTextureParameterfv");
	glgenGetTextureParameterfvEXT = (PFNGLGETTEXTUREPARAMETERFVEXTPROC) zpl__glgen_get_proc("glGetTextureParameterfvEXT");
	glgenGetTextureParameteriv = (PFNGLGETTEXTUREPARAMETERIVPROC) zpl__glgen_get_proc("glGetTextureParameteriv");
	glgenGetTextureParameterivEXT = (PFNGLGETTEXTUREPARAMETERIVEXTPROC) zpl__glgen_get_proc("glGetTextureParameterivEXT");
	glgenGetTextureSamplerHandleARB = (PFNGLGETTEXTURESAMPLERHANDLEARBPROC) zpl__glgen_get_proc("glGetTextureSamplerHandleARB");
	glgenGetTextureSamplerHandleNV = (PFNGLGETTEXTURESAMPLERHANDLENVPROC) zpl__glgen_get_proc("glGetTextureSamplerHandleNV");
	glgenGetTextureSubImage = (PFNGLGETTEXTURESUBIMAGEPROC) zpl__glgen_get_proc("glGetTextureSubImage");
	glgenGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) zpl__glgen_get_proc("glGetTransformFeedbackVarying");
	glgenGetTransformFeedbacki64_v = (PFNGLGETTRANSFORMFEEDBACKI64_VPROC) zpl__glgen_get_proc("glGetTransformFeedbacki64_v");
	glgenGetTransformFeedbacki_v = (PFNGLGETTRANSFORMFEEDBACKI_VPROC) zpl__glgen_get_proc("glGetTransformFeedbacki_v");
	glgenGetTransformFeedbackiv = (PFNGLGETTRANSFORMFEEDBACKIVPROC) zpl__glgen_get_proc("glGetTransformFeedbackiv");
	glgenGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC) zpl__glgen_get_proc("glGetUniformBlockIndex");
	glgenGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC) zpl__glgen_get_proc("glGetUniformIndices");
	glgenGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) zpl__glgen_get_proc("glGetUniformLocation");
	glgenGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC) zpl__glgen_get_proc("glGetUniformSubroutineuiv");
	glgenGetUniformdv = (PFNGLGETUNIFORMDVPROC) zpl__glgen_get_proc("glGetUniformdv");
	glgenGetUniformfv = (PFNGLGETUNIFORMFVPROC) zpl__glgen_get_proc("glGetUniformfv");
	glgenGetUniformi64vARB = (PFNGLGETUNIFORMI64VARBPROC) zpl__glgen_get_proc("glGetUniformi64vARB");
	glgenGetUniformi64vNV = (PFNGLGETUNIFORMI64VNVPROC) zpl__glgen_get_proc("glGetUniformi64vNV");
	glgenGetUniformiv = (PFNGLGETUNIFORMIVPROC) zpl__glgen_get_proc("glGetUniformiv");
	glgenGetUniformui64vARB = (PFNGLGETUNIFORMUI64VARBPROC) zpl__glgen_get_proc("glGetUniformui64vARB");
	glgenGetUniformui64vNV = (PFNGLGETUNIFORMUI64VNVPROC) zpl__glgen_get_proc("glGetUniformui64vNV");
	glgenGetUniformuiv = (PFNGLGETUNIFORMUIVPROC) zpl__glgen_get_proc("glGetUniformuiv");
	glgenGetVertexArrayIndexed64iv = (PFNGLGETVERTEXARRAYINDEXED64IVPROC) zpl__glgen_get_proc("glGetVertexArrayIndexed64iv");
	glgenGetVertexArrayIndexediv = (PFNGLGETVERTEXARRAYINDEXEDIVPROC) zpl__glgen_get_proc("glGetVertexArrayIndexediv");
	glgenGetVertexArrayIntegeri_vEXT = (PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC) zpl__glgen_get_proc("glGetVertexArrayIntegeri_vEXT");
	glgenGetVertexArrayIntegervEXT = (PFNGLGETVERTEXARRAYINTEGERVEXTPROC) zpl__glgen_get_proc("glGetVertexArrayIntegervEXT");
	glgenGetVertexArrayPointeri_vEXT = (PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC) zpl__glgen_get_proc("glGetVertexArrayPointeri_vEXT");
	glgenGetVertexArrayPointervEXT = (PFNGLGETVERTEXARRAYPOINTERVEXTPROC) zpl__glgen_get_proc("glGetVertexArrayPointervEXT");
	glgenGetVertexArrayiv = (PFNGLGETVERTEXARRAYIVPROC) zpl__glgen_get_proc("glGetVertexArrayiv");
	glgenGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC) zpl__glgen_get_proc("glGetVertexAttribIiv");
	glgenGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC) zpl__glgen_get_proc("glGetVertexAttribIuiv");
	glgenGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC) zpl__glgen_get_proc("glGetVertexAttribLdv");
	glgenGetVertexAttribLi64vNV = (PFNGLGETVERTEXATTRIBLI64VNVPROC) zpl__glgen_get_proc("glGetVertexAttribLi64vNV");
	glgenGetVertexAttribLui64vARB = (PFNGLGETVERTEXATTRIBLUI64VARBPROC) zpl__glgen_get_proc("glGetVertexAttribLui64vARB");
	glgenGetVertexAttribLui64vNV = (PFNGLGETVERTEXATTRIBLUI64VNVPROC) zpl__glgen_get_proc("glGetVertexAttribLui64vNV");
	glgenGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC) zpl__glgen_get_proc("glGetVertexAttribPointerv");
	glgenGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC) zpl__glgen_get_proc("glGetVertexAttribdv");
	glgenGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC) zpl__glgen_get_proc("glGetVertexAttribfv");
	glgenGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC) zpl__glgen_get_proc("glGetVertexAttribiv");
	glgenGetVkProcAddrNV = (PFNGLGETVKPROCADDRNVPROC) zpl__glgen_get_proc("glGetVkProcAddrNV");
	glgenGetnCompressedTexImage = (PFNGLGETNCOMPRESSEDTEXIMAGEPROC) zpl__glgen_get_proc("glGetnCompressedTexImage");
	glgenGetnCompressedTexImageARB = (PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC) zpl__glgen_get_proc("glGetnCompressedTexImageARB");
	glgenGetnTexImage = (PFNGLGETNTEXIMAGEPROC) zpl__glgen_get_proc("glGetnTexImage");
	glgenGetnTexImageARB = (PFNGLGETNTEXIMAGEARBPROC) zpl__glgen_get_proc("glGetnTexImageARB");
	glgenGetnUniformdv = (PFNGLGETNUNIFORMDVPROC) zpl__glgen_get_proc("glGetnUniformdv");
	glgenGetnUniformdvARB = (PFNGLGETNUNIFORMDVARBPROC) zpl__glgen_get_proc("glGetnUniformdvARB");
	glgenGetnUniformfv = (PFNGLGETNUNIFORMFVPROC) zpl__glgen_get_proc("glGetnUniformfv");
	glgenGetnUniformfvARB = (PFNGLGETNUNIFORMFVARBPROC) zpl__glgen_get_proc("glGetnUniformfvARB");
	glgenGetnUniformi64vARB = (PFNGLGETNUNIFORMI64VARBPROC) zpl__glgen_get_proc("glGetnUniformi64vARB");
	glgenGetnUniformiv = (PFNGLGETNUNIFORMIVPROC) zpl__glgen_get_proc("glGetnUniformiv");
	glgenGetnUniformivARB = (PFNGLGETNUNIFORMIVARBPROC) zpl__glgen_get_proc("glGetnUniformivARB");
	glgenGetnUniformui64vARB = (PFNGLGETNUNIFORMUI64VARBPROC) zpl__glgen_get_proc("glGetnUniformui64vARB");
	glgenGetnUniformuiv = (PFNGLGETNUNIFORMUIVPROC) zpl__glgen_get_proc("glGetnUniformuiv");
	glgenGetnUniformuivARB = (PFNGLGETNUNIFORMUIVARBPROC) zpl__glgen_get_proc("glGetnUniformuivARB");
	glgenHint = (PFNGLHINTPROC) zpl__glgen_get_proc("glHint");
	glgenIndexFormatNV = (PFNGLINDEXFORMATNVPROC) zpl__glgen_get_proc("glIndexFormatNV");
	glgenInsertEventMarkerEXT = (PFNGLINSERTEVENTMARKEREXTPROC) zpl__glgen_get_proc("glInsertEventMarkerEXT");
	glgenInterpolatePathsNV = (PFNGLINTERPOLATEPATHSNVPROC) zpl__glgen_get_proc("glInterpolatePathsNV");
	glgenInvalidateBufferData = (PFNGLINVALIDATEBUFFERDATAPROC) zpl__glgen_get_proc("glInvalidateBufferData");
	glgenInvalidateBufferSubData = (PFNGLINVALIDATEBUFFERSUBDATAPROC) zpl__glgen_get_proc("glInvalidateBufferSubData");
	glgenInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC) zpl__glgen_get_proc("glInvalidateFramebuffer");
	glgenInvalidateNamedFramebufferData = (PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC) zpl__glgen_get_proc("glInvalidateNamedFramebufferData");
	glgenInvalidateNamedFramebufferSubData = (PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC) zpl__glgen_get_proc("glInvalidateNamedFramebufferSubData");
	glgenInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC) zpl__glgen_get_proc("glInvalidateSubFramebuffer");
	glgenInvalidateTexImage = (PFNGLINVALIDATETEXIMAGEPROC) zpl__glgen_get_proc("glInvalidateTexImage");
	glgenInvalidateTexSubImage = (PFNGLINVALIDATETEXSUBIMAGEPROC) zpl__glgen_get_proc("glInvalidateTexSubImage");
	glgenIsBuffer = (PFNGLISBUFFERPROC) zpl__glgen_get_proc("glIsBuffer");
	glgenIsBufferResidentNV = (PFNGLISBUFFERRESIDENTNVPROC) zpl__glgen_get_proc("glIsBufferResidentNV");
	glgenIsCommandListNV = (PFNGLISCOMMANDLISTNVPROC) zpl__glgen_get_proc("glIsCommandListNV");
	glgenIsEnabled = (PFNGLISENABLEDPROC) zpl__glgen_get_proc("glIsEnabled");
	glgenIsEnabledIndexedEXT = (PFNGLISENABLEDINDEXEDEXTPROC) zpl__glgen_get_proc("glIsEnabledIndexedEXT");
	glgenIsEnabledi = (PFNGLISENABLEDIPROC) zpl__glgen_get_proc("glIsEnabledi");
	glgenIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) zpl__glgen_get_proc("glIsFramebuffer");
	glgenIsImageHandleResidentARB = (PFNGLISIMAGEHANDLERESIDENTARBPROC) zpl__glgen_get_proc("glIsImageHandleResidentARB");
	glgenIsImageHandleResidentNV = (PFNGLISIMAGEHANDLERESIDENTNVPROC) zpl__glgen_get_proc("glIsImageHandleResidentNV");
	glgenIsNamedBufferResidentNV = (PFNGLISNAMEDBUFFERRESIDENTNVPROC) zpl__glgen_get_proc("glIsNamedBufferResidentNV");
	glgenIsNamedStringARB = (PFNGLISNAMEDSTRINGARBPROC) zpl__glgen_get_proc("glIsNamedStringARB");
	glgenIsPathNV = (PFNGLISPATHNVPROC) zpl__glgen_get_proc("glIsPathNV");
	glgenIsPointInFillPathNV = (PFNGLISPOINTINFILLPATHNVPROC) zpl__glgen_get_proc("glIsPointInFillPathNV");
	glgenIsPointInStrokePathNV = (PFNGLISPOINTINSTROKEPATHNVPROC) zpl__glgen_get_proc("glIsPointInStrokePathNV");
	glgenIsProgram = (PFNGLISPROGRAMPROC) zpl__glgen_get_proc("glIsProgram");
	glgenIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC) zpl__glgen_get_proc("glIsProgramPipeline");
	glgenIsQuery = (PFNGLISQUERYPROC) zpl__glgen_get_proc("glIsQuery");
	glgenIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) zpl__glgen_get_proc("glIsRenderbuffer");
	glgenIsSampler = (PFNGLISSAMPLERPROC) zpl__glgen_get_proc("glIsSampler");
	glgenIsShader = (PFNGLISSHADERPROC) zpl__glgen_get_proc("glIsShader");
	glgenIsStateNV = (PFNGLISSTATENVPROC) zpl__glgen_get_proc("glIsStateNV");
	glgenIsSync = (PFNGLISSYNCPROC) zpl__glgen_get_proc("glIsSync");
	glgenIsTexture = (PFNGLISTEXTUREPROC) zpl__glgen_get_proc("glIsTexture");
	glgenIsTextureHandleResidentARB = (PFNGLISTEXTUREHANDLERESIDENTARBPROC) zpl__glgen_get_proc("glIsTextureHandleResidentARB");
	glgenIsTextureHandleResidentNV = (PFNGLISTEXTUREHANDLERESIDENTNVPROC) zpl__glgen_get_proc("glIsTextureHandleResidentNV");
	glgenIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC) zpl__glgen_get_proc("glIsTransformFeedback");
	glgenIsVertexArray = (PFNGLISVERTEXARRAYPROC) zpl__glgen_get_proc("glIsVertexArray");
	glgenLabelObjectEXT = (PFNGLLABELOBJECTEXTPROC) zpl__glgen_get_proc("glLabelObjectEXT");
	glgenLineWidth = (PFNGLLINEWIDTHPROC) zpl__glgen_get_proc("glLineWidth");
	glgenLinkProgram = (PFNGLLINKPROGRAMPROC) zpl__glgen_get_proc("glLinkProgram");
	glgenListDrawCommandsStatesClientNV = (PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC) zpl__glgen_get_proc("glListDrawCommandsStatesClientNV");
	glgenLogicOp = (PFNGLLOGICOPPROC) zpl__glgen_get_proc("glLogicOp");
	glgenMakeBufferNonResidentNV = (PFNGLMAKEBUFFERNONRESIDENTNVPROC) zpl__glgen_get_proc("glMakeBufferNonResidentNV");
	glgenMakeBufferResidentNV = (PFNGLMAKEBUFFERRESIDENTNVPROC) zpl__glgen_get_proc("glMakeBufferResidentNV");
	glgenMakeImageHandleNonResidentARB = (PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC) zpl__glgen_get_proc("glMakeImageHandleNonResidentARB");
	glgenMakeImageHandleNonResidentNV = (PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC) zpl__glgen_get_proc("glMakeImageHandleNonResidentNV");
	glgenMakeImageHandleResidentARB = (PFNGLMAKEIMAGEHANDLERESIDENTARBPROC) zpl__glgen_get_proc("glMakeImageHandleResidentARB");
	glgenMakeImageHandleResidentNV = (PFNGLMAKEIMAGEHANDLERESIDENTNVPROC) zpl__glgen_get_proc("glMakeImageHandleResidentNV");
	glgenMakeNamedBufferNonResidentNV = (PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC) zpl__glgen_get_proc("glMakeNamedBufferNonResidentNV");
	glgenMakeNamedBufferResidentNV = (PFNGLMAKENAMEDBUFFERRESIDENTNVPROC) zpl__glgen_get_proc("glMakeNamedBufferResidentNV");
	glgenMakeTextureHandleNonResidentARB = (PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC) zpl__glgen_get_proc("glMakeTextureHandleNonResidentARB");
	glgenMakeTextureHandleNonResidentNV = (PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC) zpl__glgen_get_proc("glMakeTextureHandleNonResidentNV");
	glgenMakeTextureHandleResidentARB = (PFNGLMAKETEXTUREHANDLERESIDENTARBPROC) zpl__glgen_get_proc("glMakeTextureHandleResidentARB");
	glgenMakeTextureHandleResidentNV = (PFNGLMAKETEXTUREHANDLERESIDENTNVPROC) zpl__glgen_get_proc("glMakeTextureHandleResidentNV");
	glgenMapBuffer = (PFNGLMAPBUFFERPROC) zpl__glgen_get_proc("glMapBuffer");
	glgenMapBufferRange = (PFNGLMAPBUFFERRANGEPROC) zpl__glgen_get_proc("glMapBufferRange");
	glgenMapNamedBuffer = (PFNGLMAPNAMEDBUFFERPROC) zpl__glgen_get_proc("glMapNamedBuffer");
	glgenMapNamedBufferEXT = (PFNGLMAPNAMEDBUFFEREXTPROC) zpl__glgen_get_proc("glMapNamedBufferEXT");
	glgenMapNamedBufferRange = (PFNGLMAPNAMEDBUFFERRANGEPROC) zpl__glgen_get_proc("glMapNamedBufferRange");
	glgenMapNamedBufferRangeEXT = (PFNGLMAPNAMEDBUFFERRANGEEXTPROC) zpl__glgen_get_proc("glMapNamedBufferRangeEXT");
	glgenMatrixFrustumEXT = (PFNGLMATRIXFRUSTUMEXTPROC) zpl__glgen_get_proc("glMatrixFrustumEXT");
	glgenMatrixLoad3x2fNV = (PFNGLMATRIXLOAD3X2FNVPROC) zpl__glgen_get_proc("glMatrixLoad3x2fNV");
	glgenMatrixLoad3x3fNV = (PFNGLMATRIXLOAD3X3FNVPROC) zpl__glgen_get_proc("glMatrixLoad3x3fNV");
	glgenMatrixLoadIdentityEXT = (PFNGLMATRIXLOADIDENTITYEXTPROC) zpl__glgen_get_proc("glMatrixLoadIdentityEXT");
	glgenMatrixLoadTranspose3x3fNV = (PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC) zpl__glgen_get_proc("glMatrixLoadTranspose3x3fNV");
	glgenMatrixLoadTransposedEXT = (PFNGLMATRIXLOADTRANSPOSEDEXTPROC) zpl__glgen_get_proc("glMatrixLoadTransposedEXT");
	glgenMatrixLoadTransposefEXT = (PFNGLMATRIXLOADTRANSPOSEFEXTPROC) zpl__glgen_get_proc("glMatrixLoadTransposefEXT");
	glgenMatrixLoaddEXT = (PFNGLMATRIXLOADDEXTPROC) zpl__glgen_get_proc("glMatrixLoaddEXT");
	glgenMatrixLoadfEXT = (PFNGLMATRIXLOADFEXTPROC) zpl__glgen_get_proc("glMatrixLoadfEXT");
	glgenMatrixMult3x2fNV = (PFNGLMATRIXMULT3X2FNVPROC) zpl__glgen_get_proc("glMatrixMult3x2fNV");
	glgenMatrixMult3x3fNV = (PFNGLMATRIXMULT3X3FNVPROC) zpl__glgen_get_proc("glMatrixMult3x3fNV");
	glgenMatrixMultTranspose3x3fNV = (PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC) zpl__glgen_get_proc("glMatrixMultTranspose3x3fNV");
	glgenMatrixMultTransposedEXT = (PFNGLMATRIXMULTTRANSPOSEDEXTPROC) zpl__glgen_get_proc("glMatrixMultTransposedEXT");
	glgenMatrixMultTransposefEXT = (PFNGLMATRIXMULTTRANSPOSEFEXTPROC) zpl__glgen_get_proc("glMatrixMultTransposefEXT");
	glgenMatrixMultdEXT = (PFNGLMATRIXMULTDEXTPROC) zpl__glgen_get_proc("glMatrixMultdEXT");
	glgenMatrixMultfEXT = (PFNGLMATRIXMULTFEXTPROC) zpl__glgen_get_proc("glMatrixMultfEXT");
	glgenMatrixOrthoEXT = (PFNGLMATRIXORTHOEXTPROC) zpl__glgen_get_proc("glMatrixOrthoEXT");
	glgenMatrixPopEXT = (PFNGLMATRIXPOPEXTPROC) zpl__glgen_get_proc("glMatrixPopEXT");
	glgenMatrixPushEXT = (PFNGLMATRIXPUSHEXTPROC) zpl__glgen_get_proc("glMatrixPushEXT");
	glgenMatrixRotatedEXT = (PFNGLMATRIXROTATEDEXTPROC) zpl__glgen_get_proc("glMatrixRotatedEXT");
	glgenMatrixRotatefEXT = (PFNGLMATRIXROTATEFEXTPROC) zpl__glgen_get_proc("glMatrixRotatefEXT");
	glgenMatrixScaledEXT = (PFNGLMATRIXSCALEDEXTPROC) zpl__glgen_get_proc("glMatrixScaledEXT");
	glgenMatrixScalefEXT = (PFNGLMATRIXSCALEFEXTPROC) zpl__glgen_get_proc("glMatrixScalefEXT");
	glgenMatrixTranslatedEXT = (PFNGLMATRIXTRANSLATEDEXTPROC) zpl__glgen_get_proc("glMatrixTranslatedEXT");
	glgenMatrixTranslatefEXT = (PFNGLMATRIXTRANSLATEFEXTPROC) zpl__glgen_get_proc("glMatrixTranslatefEXT");
	glgenMaxShaderCompilerThreadsARB = (PFNGLMAXSHADERCOMPILERTHREADSARBPROC) zpl__glgen_get_proc("glMaxShaderCompilerThreadsARB");
	glgenMaxShaderCompilerThreadsKHR = (PFNGLMAXSHADERCOMPILERTHREADSKHRPROC) zpl__glgen_get_proc("glMaxShaderCompilerThreadsKHR");
	glgenMemoryBarrier = (PFNGLMEMORYBARRIERPROC) zpl__glgen_get_proc("glMemoryBarrier");
	glgenMemoryBarrierByRegion = (PFNGLMEMORYBARRIERBYREGIONPROC) zpl__glgen_get_proc("glMemoryBarrierByRegion");
	glgenMinSampleShading = (PFNGLMINSAMPLESHADINGPROC) zpl__glgen_get_proc("glMinSampleShading");
	glgenMinSampleShadingARB = (PFNGLMINSAMPLESHADINGARBPROC) zpl__glgen_get_proc("glMinSampleShadingARB");
	glgenMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC) zpl__glgen_get_proc("glMultiDrawArrays");
	glgenMultiDrawArraysIndirect = (PFNGLMULTIDRAWARRAYSINDIRECTPROC) zpl__glgen_get_proc("glMultiDrawArraysIndirect");
	glgenMultiDrawArraysIndirectBindlessCountNV = (PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC) zpl__glgen_get_proc("glMultiDrawArraysIndirectBindlessCountNV");
	glgenMultiDrawArraysIndirectBindlessNV = (PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC) zpl__glgen_get_proc("glMultiDrawArraysIndirectBindlessNV");
	glgenMultiDrawArraysIndirectCount = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC) zpl__glgen_get_proc("glMultiDrawArraysIndirectCount");
	glgenMultiDrawArraysIndirectCountARB = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC) zpl__glgen_get_proc("glMultiDrawArraysIndirectCountARB");
	glgenMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC) zpl__glgen_get_proc("glMultiDrawElements");
	glgenMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) zpl__glgen_get_proc("glMultiDrawElementsBaseVertex");
	glgenMultiDrawElementsIndirect = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC) zpl__glgen_get_proc("glMultiDrawElementsIndirect");
	glgenMultiDrawElementsIndirectBindlessCountNV = (PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC) zpl__glgen_get_proc("glMultiDrawElementsIndirectBindlessCountNV");
	glgenMultiDrawElementsIndirectBindlessNV = (PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC) zpl__glgen_get_proc("glMultiDrawElementsIndirectBindlessNV");
	glgenMultiDrawElementsIndirectCount = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC) zpl__glgen_get_proc("glMultiDrawElementsIndirectCount");
	glgenMultiDrawElementsIndirectCountARB = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC) zpl__glgen_get_proc("glMultiDrawElementsIndirectCountARB");
	glgenMultiDrawMeshTasksIndirectCountNV = (PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC) zpl__glgen_get_proc("glMultiDrawMeshTasksIndirectCountNV");
	glgenMultiDrawMeshTasksIndirectNV = (PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC) zpl__glgen_get_proc("glMultiDrawMeshTasksIndirectNV");
	glgenMultiTexBufferEXT = (PFNGLMULTITEXBUFFEREXTPROC) zpl__glgen_get_proc("glMultiTexBufferEXT");
	glgenMultiTexCoordPointerEXT = (PFNGLMULTITEXCOORDPOINTEREXTPROC) zpl__glgen_get_proc("glMultiTexCoordPointerEXT");
	glgenMultiTexEnvfEXT = (PFNGLMULTITEXENVFEXTPROC) zpl__glgen_get_proc("glMultiTexEnvfEXT");
	glgenMultiTexEnvfvEXT = (PFNGLMULTITEXENVFVEXTPROC) zpl__glgen_get_proc("glMultiTexEnvfvEXT");
	glgenMultiTexEnviEXT = (PFNGLMULTITEXENVIEXTPROC) zpl__glgen_get_proc("glMultiTexEnviEXT");
	glgenMultiTexEnvivEXT = (PFNGLMULTITEXENVIVEXTPROC) zpl__glgen_get_proc("glMultiTexEnvivEXT");
	glgenMultiTexGendEXT = (PFNGLMULTITEXGENDEXTPROC) zpl__glgen_get_proc("glMultiTexGendEXT");
	glgenMultiTexGendvEXT = (PFNGLMULTITEXGENDVEXTPROC) zpl__glgen_get_proc("glMultiTexGendvEXT");
	glgenMultiTexGenfEXT = (PFNGLMULTITEXGENFEXTPROC) zpl__glgen_get_proc("glMultiTexGenfEXT");
	glgenMultiTexGenfvEXT = (PFNGLMULTITEXGENFVEXTPROC) zpl__glgen_get_proc("glMultiTexGenfvEXT");
	glgenMultiTexGeniEXT = (PFNGLMULTITEXGENIEXTPROC) zpl__glgen_get_proc("glMultiTexGeniEXT");
	glgenMultiTexGenivEXT = (PFNGLMULTITEXGENIVEXTPROC) zpl__glgen_get_proc("glMultiTexGenivEXT");
	glgenMultiTexImage1DEXT = (PFNGLMULTITEXIMAGE1DEXTPROC) zpl__glgen_get_proc("glMultiTexImage1DEXT");
	glgenMultiTexImage2DEXT = (PFNGLMULTITEXIMAGE2DEXTPROC) zpl__glgen_get_proc("glMultiTexImage2DEXT");
	glgenMultiTexImage3DEXT = (PFNGLMULTITEXIMAGE3DEXTPROC) zpl__glgen_get_proc("glMultiTexImage3DEXT");
	glgenMultiTexParameterIivEXT = (PFNGLMULTITEXPARAMETERIIVEXTPROC) zpl__glgen_get_proc("glMultiTexParameterIivEXT");
	glgenMultiTexParameterIuivEXT = (PFNGLMULTITEXPARAMETERIUIVEXTPROC) zpl__glgen_get_proc("glMultiTexParameterIuivEXT");
	glgenMultiTexParameterfEXT = (PFNGLMULTITEXPARAMETERFEXTPROC) zpl__glgen_get_proc("glMultiTexParameterfEXT");
	glgenMultiTexParameterfvEXT = (PFNGLMULTITEXPARAMETERFVEXTPROC) zpl__glgen_get_proc("glMultiTexParameterfvEXT");
	glgenMultiTexParameteriEXT = (PFNGLMULTITEXPARAMETERIEXTPROC) zpl__glgen_get_proc("glMultiTexParameteriEXT");
	glgenMultiTexParameterivEXT = (PFNGLMULTITEXPARAMETERIVEXTPROC) zpl__glgen_get_proc("glMultiTexParameterivEXT");
	glgenMultiTexRenderbufferEXT = (PFNGLMULTITEXRENDERBUFFEREXTPROC) zpl__glgen_get_proc("glMultiTexRenderbufferEXT");
	glgenMultiTexSubImage1DEXT = (PFNGLMULTITEXSUBIMAGE1DEXTPROC) zpl__glgen_get_proc("glMultiTexSubImage1DEXT");
	glgenMultiTexSubImage2DEXT = (PFNGLMULTITEXSUBIMAGE2DEXTPROC) zpl__glgen_get_proc("glMultiTexSubImage2DEXT");
	glgenMultiTexSubImage3DEXT = (PFNGLMULTITEXSUBIMAGE3DEXTPROC) zpl__glgen_get_proc("glMultiTexSubImage3DEXT");
	glgenNamedBufferAttachMemoryNV = (PFNGLNAMEDBUFFERATTACHMEMORYNVPROC) zpl__glgen_get_proc("glNamedBufferAttachMemoryNV");
	glgenNamedBufferData = (PFNGLNAMEDBUFFERDATAPROC) zpl__glgen_get_proc("glNamedBufferData");
	glgenNamedBufferDataEXT = (PFNGLNAMEDBUFFERDATAEXTPROC) zpl__glgen_get_proc("glNamedBufferDataEXT");
	glgenNamedBufferPageCommitmentARB = (PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC) zpl__glgen_get_proc("glNamedBufferPageCommitmentARB");
	glgenNamedBufferPageCommitmentEXT = (PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC) zpl__glgen_get_proc("glNamedBufferPageCommitmentEXT");
	glgenNamedBufferStorage = (PFNGLNAMEDBUFFERSTORAGEPROC) zpl__glgen_get_proc("glNamedBufferStorage");
	glgenNamedBufferStorageEXT = (PFNGLNAMEDBUFFERSTORAGEEXTPROC) zpl__glgen_get_proc("glNamedBufferStorageEXT");
	glgenNamedBufferSubData = (PFNGLNAMEDBUFFERSUBDATAPROC) zpl__glgen_get_proc("glNamedBufferSubData");
	glgenNamedBufferSubDataEXT = (PFNGLNAMEDBUFFERSUBDATAEXTPROC) zpl__glgen_get_proc("glNamedBufferSubDataEXT");
	glgenNamedCopyBufferSubDataEXT = (PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC) zpl__glgen_get_proc("glNamedCopyBufferSubDataEXT");
	glgenNamedFramebufferDrawBuffer = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC) zpl__glgen_get_proc("glNamedFramebufferDrawBuffer");
	glgenNamedFramebufferDrawBuffers = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC) zpl__glgen_get_proc("glNamedFramebufferDrawBuffers");
	glgenNamedFramebufferParameteri = (PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC) zpl__glgen_get_proc("glNamedFramebufferParameteri");
	glgenNamedFramebufferParameteriEXT = (PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC) zpl__glgen_get_proc("glNamedFramebufferParameteriEXT");
	glgenNamedFramebufferReadBuffer = (PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC) zpl__glgen_get_proc("glNamedFramebufferReadBuffer");
	glgenNamedFramebufferRenderbuffer = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC) zpl__glgen_get_proc("glNamedFramebufferRenderbuffer");
	glgenNamedFramebufferRenderbufferEXT = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC) zpl__glgen_get_proc("glNamedFramebufferRenderbufferEXT");
	glgenNamedFramebufferSampleLocationsfvARB = (PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC) zpl__glgen_get_proc("glNamedFramebufferSampleLocationsfvARB");
	glgenNamedFramebufferSampleLocationsfvNV = (PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) zpl__glgen_get_proc("glNamedFramebufferSampleLocationsfvNV");
	glgenNamedFramebufferTexture = (PFNGLNAMEDFRAMEBUFFERTEXTUREPROC) zpl__glgen_get_proc("glNamedFramebufferTexture");
	glgenNamedFramebufferTexture1DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC) zpl__glgen_get_proc("glNamedFramebufferTexture1DEXT");
	glgenNamedFramebufferTexture2DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC) zpl__glgen_get_proc("glNamedFramebufferTexture2DEXT");
	glgenNamedFramebufferTexture3DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC) zpl__glgen_get_proc("glNamedFramebufferTexture3DEXT");
	glgenNamedFramebufferTextureEXT = (PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC) zpl__glgen_get_proc("glNamedFramebufferTextureEXT");
	glgenNamedFramebufferTextureFaceEXT = (PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC) zpl__glgen_get_proc("glNamedFramebufferTextureFaceEXT");
	glgenNamedFramebufferTextureLayer = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC) zpl__glgen_get_proc("glNamedFramebufferTextureLayer");
	glgenNamedFramebufferTextureLayerEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC) zpl__glgen_get_proc("glNamedFramebufferTextureLayerEXT");
	glgenNamedProgramLocalParameter4dEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC) zpl__glgen_get_proc("glNamedProgramLocalParameter4dEXT");
	glgenNamedProgramLocalParameter4dvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC) zpl__glgen_get_proc("glNamedProgramLocalParameter4dvEXT");
	glgenNamedProgramLocalParameter4fEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC) zpl__glgen_get_proc("glNamedProgramLocalParameter4fEXT");
	glgenNamedProgramLocalParameter4fvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC) zpl__glgen_get_proc("glNamedProgramLocalParameter4fvEXT");
	glgenNamedProgramLocalParameterI4iEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC) zpl__glgen_get_proc("glNamedProgramLocalParameterI4iEXT");
	glgenNamedProgramLocalParameterI4ivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC) zpl__glgen_get_proc("glNamedProgramLocalParameterI4ivEXT");
	glgenNamedProgramLocalParameterI4uiEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC) zpl__glgen_get_proc("glNamedProgramLocalParameterI4uiEXT");
	glgenNamedProgramLocalParameterI4uivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC) zpl__glgen_get_proc("glNamedProgramLocalParameterI4uivEXT");
	glgenNamedProgramLocalParameters4fvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC) zpl__glgen_get_proc("glNamedProgramLocalParameters4fvEXT");
	glgenNamedProgramLocalParametersI4ivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC) zpl__glgen_get_proc("glNamedProgramLocalParametersI4ivEXT");
	glgenNamedProgramLocalParametersI4uivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC) zpl__glgen_get_proc("glNamedProgramLocalParametersI4uivEXT");
	glgenNamedProgramStringEXT = (PFNGLNAMEDPROGRAMSTRINGEXTPROC) zpl__glgen_get_proc("glNamedProgramStringEXT");
	glgenNamedRenderbufferStorage = (PFNGLNAMEDRENDERBUFFERSTORAGEPROC) zpl__glgen_get_proc("glNamedRenderbufferStorage");
	glgenNamedRenderbufferStorageEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC) zpl__glgen_get_proc("glNamedRenderbufferStorageEXT");
	glgenNamedRenderbufferStorageMultisample = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC) zpl__glgen_get_proc("glNamedRenderbufferStorageMultisample");
	glgenNamedRenderbufferStorageMultisampleAdvancedAMD = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) zpl__glgen_get_proc("glNamedRenderbufferStorageMultisampleAdvancedAMD");
	glgenNamedRenderbufferStorageMultisampleCoverageEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC) zpl__glgen_get_proc("glNamedRenderbufferStorageMultisampleCoverageEXT");
	glgenNamedRenderbufferStorageMultisampleEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) zpl__glgen_get_proc("glNamedRenderbufferStorageMultisampleEXT");
	glgenNamedStringARB = (PFNGLNAMEDSTRINGARBPROC) zpl__glgen_get_proc("glNamedStringARB");
	glgenNormalFormatNV = (PFNGLNORMALFORMATNVPROC) zpl__glgen_get_proc("glNormalFormatNV");
	glgenObjectLabel = (PFNGLOBJECTLABELPROC) zpl__glgen_get_proc("glObjectLabel");
	glgenObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC) zpl__glgen_get_proc("glObjectPtrLabel");
	glgenPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC) zpl__glgen_get_proc("glPatchParameterfv");
	glgenPatchParameteri = (PFNGLPATCHPARAMETERIPROC) zpl__glgen_get_proc("glPatchParameteri");
	glgenPathCommandsNV = (PFNGLPATHCOMMANDSNVPROC) zpl__glgen_get_proc("glPathCommandsNV");
	glgenPathCoordsNV = (PFNGLPATHCOORDSNVPROC) zpl__glgen_get_proc("glPathCoordsNV");
	glgenPathCoverDepthFuncNV = (PFNGLPATHCOVERDEPTHFUNCNVPROC) zpl__glgen_get_proc("glPathCoverDepthFuncNV");
	glgenPathDashArrayNV = (PFNGLPATHDASHARRAYNVPROC) zpl__glgen_get_proc("glPathDashArrayNV");
	glgenPathGlyphIndexArrayNV = (PFNGLPATHGLYPHINDEXARRAYNVPROC) zpl__glgen_get_proc("glPathGlyphIndexArrayNV");
	glgenPathGlyphIndexRangeNV = (PFNGLPATHGLYPHINDEXRANGENVPROC) zpl__glgen_get_proc("glPathGlyphIndexRangeNV");
	glgenPathGlyphRangeNV = (PFNGLPATHGLYPHRANGENVPROC) zpl__glgen_get_proc("glPathGlyphRangeNV");
	glgenPathGlyphsNV = (PFNGLPATHGLYPHSNVPROC) zpl__glgen_get_proc("glPathGlyphsNV");
	glgenPathMemoryGlyphIndexArrayNV = (PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC) zpl__glgen_get_proc("glPathMemoryGlyphIndexArrayNV");
	glgenPathParameterfNV = (PFNGLPATHPARAMETERFNVPROC) zpl__glgen_get_proc("glPathParameterfNV");
	glgenPathParameterfvNV = (PFNGLPATHPARAMETERFVNVPROC) zpl__glgen_get_proc("glPathParameterfvNV");
	glgenPathParameteriNV = (PFNGLPATHPARAMETERINVPROC) zpl__glgen_get_proc("glPathParameteriNV");
	glgenPathParameterivNV = (PFNGLPATHPARAMETERIVNVPROC) zpl__glgen_get_proc("glPathParameterivNV");
	glgenPathStencilDepthOffsetNV = (PFNGLPATHSTENCILDEPTHOFFSETNVPROC) zpl__glgen_get_proc("glPathStencilDepthOffsetNV");
	glgenPathStencilFuncNV = (PFNGLPATHSTENCILFUNCNVPROC) zpl__glgen_get_proc("glPathStencilFuncNV");
	glgenPathStringNV = (PFNGLPATHSTRINGNVPROC) zpl__glgen_get_proc("glPathStringNV");
	glgenPathSubCommandsNV = (PFNGLPATHSUBCOMMANDSNVPROC) zpl__glgen_get_proc("glPathSubCommandsNV");
	glgenPathSubCoordsNV = (PFNGLPATHSUBCOORDSNVPROC) zpl__glgen_get_proc("glPathSubCoordsNV");
	glgenPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC) zpl__glgen_get_proc("glPauseTransformFeedback");
	glgenPixelStoref = (PFNGLPIXELSTOREFPROC) zpl__glgen_get_proc("glPixelStoref");
	glgenPixelStorei = (PFNGLPIXELSTOREIPROC) zpl__glgen_get_proc("glPixelStorei");
	glgenPointAlongPathNV = (PFNGLPOINTALONGPATHNVPROC) zpl__glgen_get_proc("glPointAlongPathNV");
	glgenPointParameterf = (PFNGLPOINTPARAMETERFPROC) zpl__glgen_get_proc("glPointParameterf");
	glgenPointParameterfv = (PFNGLPOINTPARAMETERFVPROC) zpl__glgen_get_proc("glPointParameterfv");
	glgenPointParameteri = (PFNGLPOINTPARAMETERIPROC) zpl__glgen_get_proc("glPointParameteri");
	glgenPointParameteriv = (PFNGLPOINTPARAMETERIVPROC) zpl__glgen_get_proc("glPointParameteriv");
	glgenPointSize = (PFNGLPOINTSIZEPROC) zpl__glgen_get_proc("glPointSize");
	glgenPolygonMode = (PFNGLPOLYGONMODEPROC) zpl__glgen_get_proc("glPolygonMode");
	glgenPolygonOffset = (PFNGLPOLYGONOFFSETPROC) zpl__glgen_get_proc("glPolygonOffset");
	glgenPolygonOffsetClamp = (PFNGLPOLYGONOFFSETCLAMPPROC) zpl__glgen_get_proc("glPolygonOffsetClamp");
	glgenPolygonOffsetClampEXT = (PFNGLPOLYGONOFFSETCLAMPEXTPROC) zpl__glgen_get_proc("glPolygonOffsetClampEXT");
	glgenPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC) zpl__glgen_get_proc("glPopDebugGroup");
	glgenPopGroupMarkerEXT = (PFNGLPOPGROUPMARKEREXTPROC) zpl__glgen_get_proc("glPopGroupMarkerEXT");
	glgenPrimitiveBoundingBoxARB = (PFNGLPRIMITIVEBOUNDINGBOXARBPROC) zpl__glgen_get_proc("glPrimitiveBoundingBoxARB");
	glgenPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC) zpl__glgen_get_proc("glPrimitiveRestartIndex");
	glgenProgramBinary = (PFNGLPROGRAMBINARYPROC) zpl__glgen_get_proc("glProgramBinary");
	glgenProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC) zpl__glgen_get_proc("glProgramParameteri");
	glgenProgramParameteriARB = (PFNGLPROGRAMPARAMETERIARBPROC) zpl__glgen_get_proc("glProgramParameteriARB");
	glgenProgramPathFragmentInputGenNV = (PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC) zpl__glgen_get_proc("glProgramPathFragmentInputGenNV");
	glgenProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC) zpl__glgen_get_proc("glProgramUniform1d");
	glgenProgramUniform1dEXT = (PFNGLPROGRAMUNIFORM1DEXTPROC) zpl__glgen_get_proc("glProgramUniform1dEXT");
	glgenProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC) zpl__glgen_get_proc("glProgramUniform1dv");
	glgenProgramUniform1dvEXT = (PFNGLPROGRAMUNIFORM1DVEXTPROC) zpl__glgen_get_proc("glProgramUniform1dvEXT");
	glgenProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC) zpl__glgen_get_proc("glProgramUniform1f");
	glgenProgramUniform1fEXT = (PFNGLPROGRAMUNIFORM1FEXTPROC) zpl__glgen_get_proc("glProgramUniform1fEXT");
	glgenProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC) zpl__glgen_get_proc("glProgramUniform1fv");
	glgenProgramUniform1fvEXT = (PFNGLPROGRAMUNIFORM1FVEXTPROC) zpl__glgen_get_proc("glProgramUniform1fvEXT");
	glgenProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC) zpl__glgen_get_proc("glProgramUniform1i");
	glgenProgramUniform1i64ARB = (PFNGLPROGRAMUNIFORM1I64ARBPROC) zpl__glgen_get_proc("glProgramUniform1i64ARB");
	glgenProgramUniform1i64NV = (PFNGLPROGRAMUNIFORM1I64NVPROC) zpl__glgen_get_proc("glProgramUniform1i64NV");
	glgenProgramUniform1i64vARB = (PFNGLPROGRAMUNIFORM1I64VARBPROC) zpl__glgen_get_proc("glProgramUniform1i64vARB");
	glgenProgramUniform1i64vNV = (PFNGLPROGRAMUNIFORM1I64VNVPROC) zpl__glgen_get_proc("glProgramUniform1i64vNV");
	glgenProgramUniform1iEXT = (PFNGLPROGRAMUNIFORM1IEXTPROC) zpl__glgen_get_proc("glProgramUniform1iEXT");
	glgenProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC) zpl__glgen_get_proc("glProgramUniform1iv");
	glgenProgramUniform1ivEXT = (PFNGLPROGRAMUNIFORM1IVEXTPROC) zpl__glgen_get_proc("glProgramUniform1ivEXT");
	glgenProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC) zpl__glgen_get_proc("glProgramUniform1ui");
	glgenProgramUniform1ui64ARB = (PFNGLPROGRAMUNIFORM1UI64ARBPROC) zpl__glgen_get_proc("glProgramUniform1ui64ARB");
	glgenProgramUniform1ui64NV = (PFNGLPROGRAMUNIFORM1UI64NVPROC) zpl__glgen_get_proc("glProgramUniform1ui64NV");
	glgenProgramUniform1ui64vARB = (PFNGLPROGRAMUNIFORM1UI64VARBPROC) zpl__glgen_get_proc("glProgramUniform1ui64vARB");
	glgenProgramUniform1ui64vNV = (PFNGLPROGRAMUNIFORM1UI64VNVPROC) zpl__glgen_get_proc("glProgramUniform1ui64vNV");
	glgenProgramUniform1uiEXT = (PFNGLPROGRAMUNIFORM1UIEXTPROC) zpl__glgen_get_proc("glProgramUniform1uiEXT");
	glgenProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC) zpl__glgen_get_proc("glProgramUniform1uiv");
	glgenProgramUniform1uivEXT = (PFNGLPROGRAMUNIFORM1UIVEXTPROC) zpl__glgen_get_proc("glProgramUniform1uivEXT");
	glgenProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC) zpl__glgen_get_proc("glProgramUniform2d");
	glgenProgramUniform2dEXT = (PFNGLPROGRAMUNIFORM2DEXTPROC) zpl__glgen_get_proc("glProgramUniform2dEXT");
	glgenProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC) zpl__glgen_get_proc("glProgramUniform2dv");
	glgenProgramUniform2dvEXT = (PFNGLPROGRAMUNIFORM2DVEXTPROC) zpl__glgen_get_proc("glProgramUniform2dvEXT");
	glgenProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC) zpl__glgen_get_proc("glProgramUniform2f");
	glgenProgramUniform2fEXT = (PFNGLPROGRAMUNIFORM2FEXTPROC) zpl__glgen_get_proc("glProgramUniform2fEXT");
	glgenProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC) zpl__glgen_get_proc("glProgramUniform2fv");
	glgenProgramUniform2fvEXT = (PFNGLPROGRAMUNIFORM2FVEXTPROC) zpl__glgen_get_proc("glProgramUniform2fvEXT");
	glgenProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC) zpl__glgen_get_proc("glProgramUniform2i");
	glgenProgramUniform2i64ARB = (PFNGLPROGRAMUNIFORM2I64ARBPROC) zpl__glgen_get_proc("glProgramUniform2i64ARB");
	glgenProgramUniform2i64NV = (PFNGLPROGRAMUNIFORM2I64NVPROC) zpl__glgen_get_proc("glProgramUniform2i64NV");
	glgenProgramUniform2i64vARB = (PFNGLPROGRAMUNIFORM2I64VARBPROC) zpl__glgen_get_proc("glProgramUniform2i64vARB");
	glgenProgramUniform2i64vNV = (PFNGLPROGRAMUNIFORM2I64VNVPROC) zpl__glgen_get_proc("glProgramUniform2i64vNV");
	glgenProgramUniform2iEXT = (PFNGLPROGRAMUNIFORM2IEXTPROC) zpl__glgen_get_proc("glProgramUniform2iEXT");
	glgenProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC) zpl__glgen_get_proc("glProgramUniform2iv");
	glgenProgramUniform2ivEXT = (PFNGLPROGRAMUNIFORM2IVEXTPROC) zpl__glgen_get_proc("glProgramUniform2ivEXT");
	glgenProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC) zpl__glgen_get_proc("glProgramUniform2ui");
	glgenProgramUniform2ui64ARB = (PFNGLPROGRAMUNIFORM2UI64ARBPROC) zpl__glgen_get_proc("glProgramUniform2ui64ARB");
	glgenProgramUniform2ui64NV = (PFNGLPROGRAMUNIFORM2UI64NVPROC) zpl__glgen_get_proc("glProgramUniform2ui64NV");
	glgenProgramUniform2ui64vARB = (PFNGLPROGRAMUNIFORM2UI64VARBPROC) zpl__glgen_get_proc("glProgramUniform2ui64vARB");
	glgenProgramUniform2ui64vNV = (PFNGLPROGRAMUNIFORM2UI64VNVPROC) zpl__glgen_get_proc("glProgramUniform2ui64vNV");
	glgenProgramUniform2uiEXT = (PFNGLPROGRAMUNIFORM2UIEXTPROC) zpl__glgen_get_proc("glProgramUniform2uiEXT");
	glgenProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC) zpl__glgen_get_proc("glProgramUniform2uiv");
	glgenProgramUniform2uivEXT = (PFNGLPROGRAMUNIFORM2UIVEXTPROC) zpl__glgen_get_proc("glProgramUniform2uivEXT");
	glgenProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC) zpl__glgen_get_proc("glProgramUniform3d");
	glgenProgramUniform3dEXT = (PFNGLPROGRAMUNIFORM3DEXTPROC) zpl__glgen_get_proc("glProgramUniform3dEXT");
	glgenProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC) zpl__glgen_get_proc("glProgramUniform3dv");
	glgenProgramUniform3dvEXT = (PFNGLPROGRAMUNIFORM3DVEXTPROC) zpl__glgen_get_proc("glProgramUniform3dvEXT");
	glgenProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC) zpl__glgen_get_proc("glProgramUniform3f");
	glgenProgramUniform3fEXT = (PFNGLPROGRAMUNIFORM3FEXTPROC) zpl__glgen_get_proc("glProgramUniform3fEXT");
	glgenProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC) zpl__glgen_get_proc("glProgramUniform3fv");
	glgenProgramUniform3fvEXT = (PFNGLPROGRAMUNIFORM3FVEXTPROC) zpl__glgen_get_proc("glProgramUniform3fvEXT");
	glgenProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC) zpl__glgen_get_proc("glProgramUniform3i");
	glgenProgramUniform3i64ARB = (PFNGLPROGRAMUNIFORM3I64ARBPROC) zpl__glgen_get_proc("glProgramUniform3i64ARB");
	glgenProgramUniform3i64NV = (PFNGLPROGRAMUNIFORM3I64NVPROC) zpl__glgen_get_proc("glProgramUniform3i64NV");
	glgenProgramUniform3i64vARB = (PFNGLPROGRAMUNIFORM3I64VARBPROC) zpl__glgen_get_proc("glProgramUniform3i64vARB");
	glgenProgramUniform3i64vNV = (PFNGLPROGRAMUNIFORM3I64VNVPROC) zpl__glgen_get_proc("glProgramUniform3i64vNV");
	glgenProgramUniform3iEXT = (PFNGLPROGRAMUNIFORM3IEXTPROC) zpl__glgen_get_proc("glProgramUniform3iEXT");
	glgenProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC) zpl__glgen_get_proc("glProgramUniform3iv");
	glgenProgramUniform3ivEXT = (PFNGLPROGRAMUNIFORM3IVEXTPROC) zpl__glgen_get_proc("glProgramUniform3ivEXT");
	glgenProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC) zpl__glgen_get_proc("glProgramUniform3ui");
	glgenProgramUniform3ui64ARB = (PFNGLPROGRAMUNIFORM3UI64ARBPROC) zpl__glgen_get_proc("glProgramUniform3ui64ARB");
	glgenProgramUniform3ui64NV = (PFNGLPROGRAMUNIFORM3UI64NVPROC) zpl__glgen_get_proc("glProgramUniform3ui64NV");
	glgenProgramUniform3ui64vARB = (PFNGLPROGRAMUNIFORM3UI64VARBPROC) zpl__glgen_get_proc("glProgramUniform3ui64vARB");
	glgenProgramUniform3ui64vNV = (PFNGLPROGRAMUNIFORM3UI64VNVPROC) zpl__glgen_get_proc("glProgramUniform3ui64vNV");
	glgenProgramUniform3uiEXT = (PFNGLPROGRAMUNIFORM3UIEXTPROC) zpl__glgen_get_proc("glProgramUniform3uiEXT");
	glgenProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC) zpl__glgen_get_proc("glProgramUniform3uiv");
	glgenProgramUniform3uivEXT = (PFNGLPROGRAMUNIFORM3UIVEXTPROC) zpl__glgen_get_proc("glProgramUniform3uivEXT");
	glgenProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC) zpl__glgen_get_proc("glProgramUniform4d");
	glgenProgramUniform4dEXT = (PFNGLPROGRAMUNIFORM4DEXTPROC) zpl__glgen_get_proc("glProgramUniform4dEXT");
	glgenProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC) zpl__glgen_get_proc("glProgramUniform4dv");
	glgenProgramUniform4dvEXT = (PFNGLPROGRAMUNIFORM4DVEXTPROC) zpl__glgen_get_proc("glProgramUniform4dvEXT");
	glgenProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC) zpl__glgen_get_proc("glProgramUniform4f");
	glgenProgramUniform4fEXT = (PFNGLPROGRAMUNIFORM4FEXTPROC) zpl__glgen_get_proc("glProgramUniform4fEXT");
	glgenProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC) zpl__glgen_get_proc("glProgramUniform4fv");
	glgenProgramUniform4fvEXT = (PFNGLPROGRAMUNIFORM4FVEXTPROC) zpl__glgen_get_proc("glProgramUniform4fvEXT");
	glgenProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC) zpl__glgen_get_proc("glProgramUniform4i");
	glgenProgramUniform4i64ARB = (PFNGLPROGRAMUNIFORM4I64ARBPROC) zpl__glgen_get_proc("glProgramUniform4i64ARB");
	glgenProgramUniform4i64NV = (PFNGLPROGRAMUNIFORM4I64NVPROC) zpl__glgen_get_proc("glProgramUniform4i64NV");
	glgenProgramUniform4i64vARB = (PFNGLPROGRAMUNIFORM4I64VARBPROC) zpl__glgen_get_proc("glProgramUniform4i64vARB");
	glgenProgramUniform4i64vNV = (PFNGLPROGRAMUNIFORM4I64VNVPROC) zpl__glgen_get_proc("glProgramUniform4i64vNV");
	glgenProgramUniform4iEXT = (PFNGLPROGRAMUNIFORM4IEXTPROC) zpl__glgen_get_proc("glProgramUniform4iEXT");
	glgenProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC) zpl__glgen_get_proc("glProgramUniform4iv");
	glgenProgramUniform4ivEXT = (PFNGLPROGRAMUNIFORM4IVEXTPROC) zpl__glgen_get_proc("glProgramUniform4ivEXT");
	glgenProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC) zpl__glgen_get_proc("glProgramUniform4ui");
	glgenProgramUniform4ui64ARB = (PFNGLPROGRAMUNIFORM4UI64ARBPROC) zpl__glgen_get_proc("glProgramUniform4ui64ARB");
	glgenProgramUniform4ui64NV = (PFNGLPROGRAMUNIFORM4UI64NVPROC) zpl__glgen_get_proc("glProgramUniform4ui64NV");
	glgenProgramUniform4ui64vARB = (PFNGLPROGRAMUNIFORM4UI64VARBPROC) zpl__glgen_get_proc("glProgramUniform4ui64vARB");
	glgenProgramUniform4ui64vNV = (PFNGLPROGRAMUNIFORM4UI64VNVPROC) zpl__glgen_get_proc("glProgramUniform4ui64vNV");
	glgenProgramUniform4uiEXT = (PFNGLPROGRAMUNIFORM4UIEXTPROC) zpl__glgen_get_proc("glProgramUniform4uiEXT");
	glgenProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC) zpl__glgen_get_proc("glProgramUniform4uiv");
	glgenProgramUniform4uivEXT = (PFNGLPROGRAMUNIFORM4UIVEXTPROC) zpl__glgen_get_proc("glProgramUniform4uivEXT");
	glgenProgramUniformHandleui64ARB = (PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC) zpl__glgen_get_proc("glProgramUniformHandleui64ARB");
	glgenProgramUniformHandleui64NV = (PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC) zpl__glgen_get_proc("glProgramUniformHandleui64NV");
	glgenProgramUniformHandleui64vARB = (PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC) zpl__glgen_get_proc("glProgramUniformHandleui64vARB");
	glgenProgramUniformHandleui64vNV = (PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC) zpl__glgen_get_proc("glProgramUniformHandleui64vNV");
	glgenProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC) zpl__glgen_get_proc("glProgramUniformMatrix2dv");
	glgenProgramUniformMatrix2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix2dvEXT");
	glgenProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC) zpl__glgen_get_proc("glProgramUniformMatrix2fv");
	glgenProgramUniformMatrix2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix2fvEXT");
	glgenProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC) zpl__glgen_get_proc("glProgramUniformMatrix2x3dv");
	glgenProgramUniformMatrix2x3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix2x3dvEXT");
	glgenProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) zpl__glgen_get_proc("glProgramUniformMatrix2x3fv");
	glgenProgramUniformMatrix2x3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix2x3fvEXT");
	glgenProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC) zpl__glgen_get_proc("glProgramUniformMatrix2x4dv");
	glgenProgramUniformMatrix2x4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix2x4dvEXT");
	glgenProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) zpl__glgen_get_proc("glProgramUniformMatrix2x4fv");
	glgenProgramUniformMatrix2x4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix2x4fvEXT");
	glgenProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC) zpl__glgen_get_proc("glProgramUniformMatrix3dv");
	glgenProgramUniformMatrix3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix3dvEXT");
	glgenProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC) zpl__glgen_get_proc("glProgramUniformMatrix3fv");
	glgenProgramUniformMatrix3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix3fvEXT");
	glgenProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC) zpl__glgen_get_proc("glProgramUniformMatrix3x2dv");
	glgenProgramUniformMatrix3x2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix3x2dvEXT");
	glgenProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) zpl__glgen_get_proc("glProgramUniformMatrix3x2fv");
	glgenProgramUniformMatrix3x2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix3x2fvEXT");
	glgenProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC) zpl__glgen_get_proc("glProgramUniformMatrix3x4dv");
	glgenProgramUniformMatrix3x4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix3x4dvEXT");
	glgenProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) zpl__glgen_get_proc("glProgramUniformMatrix3x4fv");
	glgenProgramUniformMatrix3x4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix3x4fvEXT");
	glgenProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC) zpl__glgen_get_proc("glProgramUniformMatrix4dv");
	glgenProgramUniformMatrix4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix4dvEXT");
	glgenProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC) zpl__glgen_get_proc("glProgramUniformMatrix4fv");
	glgenProgramUniformMatrix4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix4fvEXT");
	glgenProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC) zpl__glgen_get_proc("glProgramUniformMatrix4x2dv");
	glgenProgramUniformMatrix4x2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix4x2dvEXT");
	glgenProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) zpl__glgen_get_proc("glProgramUniformMatrix4x2fv");
	glgenProgramUniformMatrix4x2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix4x2fvEXT");
	glgenProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC) zpl__glgen_get_proc("glProgramUniformMatrix4x3dv");
	glgenProgramUniformMatrix4x3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix4x3dvEXT");
	glgenProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) zpl__glgen_get_proc("glProgramUniformMatrix4x3fv");
	glgenProgramUniformMatrix4x3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) zpl__glgen_get_proc("glProgramUniformMatrix4x3fvEXT");
	glgenProgramUniformui64NV = (PFNGLPROGRAMUNIFORMUI64NVPROC) zpl__glgen_get_proc("glProgramUniformui64NV");
	glgenProgramUniformui64vNV = (PFNGLPROGRAMUNIFORMUI64VNVPROC) zpl__glgen_get_proc("glProgramUniformui64vNV");
	glgenProvokingVertex = (PFNGLPROVOKINGVERTEXPROC) zpl__glgen_get_proc("glProvokingVertex");
	glgenPushClientAttribDefaultEXT = (PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC) zpl__glgen_get_proc("glPushClientAttribDefaultEXT");
	glgenPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC) zpl__glgen_get_proc("glPushDebugGroup");
	glgenPushGroupMarkerEXT = (PFNGLPUSHGROUPMARKEREXTPROC) zpl__glgen_get_proc("glPushGroupMarkerEXT");
	glgenQueryCounter = (PFNGLQUERYCOUNTERPROC) zpl__glgen_get_proc("glQueryCounter");
	glgenRasterSamplesEXT = (PFNGLRASTERSAMPLESEXTPROC) zpl__glgen_get_proc("glRasterSamplesEXT");
	glgenReadBuffer = (PFNGLREADBUFFERPROC) zpl__glgen_get_proc("glReadBuffer");
	glgenReadPixels = (PFNGLREADPIXELSPROC) zpl__glgen_get_proc("glReadPixels");
	glgenReadnPixels = (PFNGLREADNPIXELSPROC) zpl__glgen_get_proc("glReadnPixels");
	glgenReadnPixelsARB = (PFNGLREADNPIXELSARBPROC) zpl__glgen_get_proc("glReadnPixelsARB");
	glgenReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC) zpl__glgen_get_proc("glReleaseShaderCompiler");
	glgenRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) zpl__glgen_get_proc("glRenderbufferStorage");
	glgenRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) zpl__glgen_get_proc("glRenderbufferStorageMultisample");
	glgenRenderbufferStorageMultisampleAdvancedAMD = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) zpl__glgen_get_proc("glRenderbufferStorageMultisampleAdvancedAMD");
	glgenRenderbufferStorageMultisampleCoverageNV = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC) zpl__glgen_get_proc("glRenderbufferStorageMultisampleCoverageNV");
	glgenResetMemoryObjectParameterNV = (PFNGLRESETMEMORYOBJECTPARAMETERNVPROC) zpl__glgen_get_proc("glResetMemoryObjectParameterNV");
	glgenResolveDepthValuesNV = (PFNGLRESOLVEDEPTHVALUESNVPROC) zpl__glgen_get_proc("glResolveDepthValuesNV");
	glgenResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC) zpl__glgen_get_proc("glResumeTransformFeedback");
	glgenSampleCoverage = (PFNGLSAMPLECOVERAGEPROC) zpl__glgen_get_proc("glSampleCoverage");
	glgenSampleMaski = (PFNGLSAMPLEMASKIPROC) zpl__glgen_get_proc("glSampleMaski");
	glgenSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC) zpl__glgen_get_proc("glSamplerParameterIiv");
	glgenSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC) zpl__glgen_get_proc("glSamplerParameterIuiv");
	glgenSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC) zpl__glgen_get_proc("glSamplerParameterf");
	glgenSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC) zpl__glgen_get_proc("glSamplerParameterfv");
	glgenSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC) zpl__glgen_get_proc("glSamplerParameteri");
	glgenSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC) zpl__glgen_get_proc("glSamplerParameteriv");
	glgenScissor = (PFNGLSCISSORPROC) zpl__glgen_get_proc("glScissor");
	glgenScissorArrayv = (PFNGLSCISSORARRAYVPROC) zpl__glgen_get_proc("glScissorArrayv");
	glgenScissorExclusiveArrayvNV = (PFNGLSCISSOREXCLUSIVEARRAYVNVPROC) zpl__glgen_get_proc("glScissorExclusiveArrayvNV");
	glgenScissorExclusiveNV = (PFNGLSCISSOREXCLUSIVENVPROC) zpl__glgen_get_proc("glScissorExclusiveNV");
	glgenScissorIndexed = (PFNGLSCISSORINDEXEDPROC) zpl__glgen_get_proc("glScissorIndexed");
	glgenScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC) zpl__glgen_get_proc("glScissorIndexedv");
	glgenSecondaryColorFormatNV = (PFNGLSECONDARYCOLORFORMATNVPROC) zpl__glgen_get_proc("glSecondaryColorFormatNV");
	glgenSelectPerfMonitorCountersAMD = (PFNGLSELECTPERFMONITORCOUNTERSAMDPROC) zpl__glgen_get_proc("glSelectPerfMonitorCountersAMD");
	glgenShaderBinary = (PFNGLSHADERBINARYPROC) zpl__glgen_get_proc("glShaderBinary");
	glgenShaderSource = (PFNGLSHADERSOURCEPROC) zpl__glgen_get_proc("glShaderSource");
	glgenShaderStorageBlockBinding = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC) zpl__glgen_get_proc("glShaderStorageBlockBinding");
	glgenShadingRateImageBarrierNV = (PFNGLSHADINGRATEIMAGEBARRIERNVPROC) zpl__glgen_get_proc("glShadingRateImageBarrierNV");
	glgenShadingRateImagePaletteNV = (PFNGLSHADINGRATEIMAGEPALETTENVPROC) zpl__glgen_get_proc("glShadingRateImagePaletteNV");
	glgenShadingRateSampleOrderCustomNV = (PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC) zpl__glgen_get_proc("glShadingRateSampleOrderCustomNV");
	glgenShadingRateSampleOrderNV = (PFNGLSHADINGRATESAMPLEORDERNVPROC) zpl__glgen_get_proc("glShadingRateSampleOrderNV");
	glgenSignalVkFenceNV = (PFNGLSIGNALVKFENCENVPROC) zpl__glgen_get_proc("glSignalVkFenceNV");
	glgenSignalVkSemaphoreNV = (PFNGLSIGNALVKSEMAPHORENVPROC) zpl__glgen_get_proc("glSignalVkSemaphoreNV");
	glgenSpecializeShader = (PFNGLSPECIALIZESHADERPROC) zpl__glgen_get_proc("glSpecializeShader");
	glgenSpecializeShaderARB = (PFNGLSPECIALIZESHADERARBPROC) zpl__glgen_get_proc("glSpecializeShaderARB");
	glgenStateCaptureNV = (PFNGLSTATECAPTURENVPROC) zpl__glgen_get_proc("glStateCaptureNV");
	glgenStencilFillPathInstancedNV = (PFNGLSTENCILFILLPATHINSTANCEDNVPROC) zpl__glgen_get_proc("glStencilFillPathInstancedNV");
	glgenStencilFillPathNV = (PFNGLSTENCILFILLPATHNVPROC) zpl__glgen_get_proc("glStencilFillPathNV");
	glgenStencilFunc = (PFNGLSTENCILFUNCPROC) zpl__glgen_get_proc("glStencilFunc");
	glgenStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC) zpl__glgen_get_proc("glStencilFuncSeparate");
	glgenStencilMask = (PFNGLSTENCILMASKPROC) zpl__glgen_get_proc("glStencilMask");
	glgenStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC) zpl__glgen_get_proc("glStencilMaskSeparate");
	glgenStencilOp = (PFNGLSTENCILOPPROC) zpl__glgen_get_proc("glStencilOp");
	glgenStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC) zpl__glgen_get_proc("glStencilOpSeparate");
	glgenStencilStrokePathInstancedNV = (PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC) zpl__glgen_get_proc("glStencilStrokePathInstancedNV");
	glgenStencilStrokePathNV = (PFNGLSTENCILSTROKEPATHNVPROC) zpl__glgen_get_proc("glStencilStrokePathNV");
	glgenStencilThenCoverFillPathInstancedNV = (PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC) zpl__glgen_get_proc("glStencilThenCoverFillPathInstancedNV");
	glgenStencilThenCoverFillPathNV = (PFNGLSTENCILTHENCOVERFILLPATHNVPROC) zpl__glgen_get_proc("glStencilThenCoverFillPathNV");
	glgenStencilThenCoverStrokePathInstancedNV = (PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC) zpl__glgen_get_proc("glStencilThenCoverStrokePathInstancedNV");
	glgenStencilThenCoverStrokePathNV = (PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC) zpl__glgen_get_proc("glStencilThenCoverStrokePathNV");
	glgenSubpixelPrecisionBiasNV = (PFNGLSUBPIXELPRECISIONBIASNVPROC) zpl__glgen_get_proc("glSubpixelPrecisionBiasNV");
	glgenTexAttachMemoryNV = (PFNGLTEXATTACHMEMORYNVPROC) zpl__glgen_get_proc("glTexAttachMemoryNV");
	glgenTexBuffer = (PFNGLTEXBUFFERPROC) zpl__glgen_get_proc("glTexBuffer");
	glgenTexBufferARB = (PFNGLTEXBUFFERARBPROC) zpl__glgen_get_proc("glTexBufferARB");
	glgenTexBufferRange = (PFNGLTEXBUFFERRANGEPROC) zpl__glgen_get_proc("glTexBufferRange");
	glgenTexCoordFormatNV = (PFNGLTEXCOORDFORMATNVPROC) zpl__glgen_get_proc("glTexCoordFormatNV");
	glgenTexImage1D = (PFNGLTEXIMAGE1DPROC) zpl__glgen_get_proc("glTexImage1D");
	glgenTexImage2D = (PFNGLTEXIMAGE2DPROC) zpl__glgen_get_proc("glTexImage2D");
	glgenTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC) zpl__glgen_get_proc("glTexImage2DMultisample");
	glgenTexImage3D = (PFNGLTEXIMAGE3DPROC) zpl__glgen_get_proc("glTexImage3D");
	glgenTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC) zpl__glgen_get_proc("glTexImage3DMultisample");
	glgenTexPageCommitmentARB = (PFNGLTEXPAGECOMMITMENTARBPROC) zpl__glgen_get_proc("glTexPageCommitmentARB");
	glgenTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC) zpl__glgen_get_proc("glTexParameterIiv");
	glgenTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC) zpl__glgen_get_proc("glTexParameterIuiv");
	glgenTexParameterf = (PFNGLTEXPARAMETERFPROC) zpl__glgen_get_proc("glTexParameterf");
	glgenTexParameterfv = (PFNGLTEXPARAMETERFVPROC) zpl__glgen_get_proc("glTexParameterfv");
	glgenTexParameteri = (PFNGLTEXPARAMETERIPROC) zpl__glgen_get_proc("glTexParameteri");
	glgenTexParameteriv = (PFNGLTEXPARAMETERIVPROC) zpl__glgen_get_proc("glTexParameteriv");
	glgenTexStorage1D = (PFNGLTEXSTORAGE1DPROC) zpl__glgen_get_proc("glTexStorage1D");
	glgenTexStorage2D = (PFNGLTEXSTORAGE2DPROC) zpl__glgen_get_proc("glTexStorage2D");
	glgenTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC) zpl__glgen_get_proc("glTexStorage2DMultisample");
	glgenTexStorage3D = (PFNGLTEXSTORAGE3DPROC) zpl__glgen_get_proc("glTexStorage3D");
	glgenTexStorage3DMultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC) zpl__glgen_get_proc("glTexStorage3DMultisample");
	glgenTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC) zpl__glgen_get_proc("glTexSubImage1D");
	glgenTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC) zpl__glgen_get_proc("glTexSubImage2D");
	glgenTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC) zpl__glgen_get_proc("glTexSubImage3D");
	glgenTextureAttachMemoryNV = (PFNGLTEXTUREATTACHMEMORYNVPROC) zpl__glgen_get_proc("glTextureAttachMemoryNV");
	glgenTextureBarrier = (PFNGLTEXTUREBARRIERPROC) zpl__glgen_get_proc("glTextureBarrier");
	glgenTextureBarrierNV = (PFNGLTEXTUREBARRIERNVPROC) zpl__glgen_get_proc("glTextureBarrierNV");
	glgenTextureBuffer = (PFNGLTEXTUREBUFFERPROC) zpl__glgen_get_proc("glTextureBuffer");
	glgenTextureBufferEXT = (PFNGLTEXTUREBUFFEREXTPROC) zpl__glgen_get_proc("glTextureBufferEXT");
	glgenTextureBufferRange = (PFNGLTEXTUREBUFFERRANGEPROC) zpl__glgen_get_proc("glTextureBufferRange");
	glgenTextureBufferRangeEXT = (PFNGLTEXTUREBUFFERRANGEEXTPROC) zpl__glgen_get_proc("glTextureBufferRangeEXT");
	glgenTextureImage1DEXT = (PFNGLTEXTUREIMAGE1DEXTPROC) zpl__glgen_get_proc("glTextureImage1DEXT");
	glgenTextureImage2DEXT = (PFNGLTEXTUREIMAGE2DEXTPROC) zpl__glgen_get_proc("glTextureImage2DEXT");
	glgenTextureImage3DEXT = (PFNGLTEXTUREIMAGE3DEXTPROC) zpl__glgen_get_proc("glTextureImage3DEXT");
	glgenTexturePageCommitmentEXT = (PFNGLTEXTUREPAGECOMMITMENTEXTPROC) zpl__glgen_get_proc("glTexturePageCommitmentEXT");
	glgenTextureParameterIiv = (PFNGLTEXTUREPARAMETERIIVPROC) zpl__glgen_get_proc("glTextureParameterIiv");
	glgenTextureParameterIivEXT = (PFNGLTEXTUREPARAMETERIIVEXTPROC) zpl__glgen_get_proc("glTextureParameterIivEXT");
	glgenTextureParameterIuiv = (PFNGLTEXTUREPARAMETERIUIVPROC) zpl__glgen_get_proc("glTextureParameterIuiv");
	glgenTextureParameterIuivEXT = (PFNGLTEXTUREPARAMETERIUIVEXTPROC) zpl__glgen_get_proc("glTextureParameterIuivEXT");
	glgenTextureParameterf = (PFNGLTEXTUREPARAMETERFPROC) zpl__glgen_get_proc("glTextureParameterf");
	glgenTextureParameterfEXT = (PFNGLTEXTUREPARAMETERFEXTPROC) zpl__glgen_get_proc("glTextureParameterfEXT");
	glgenTextureParameterfv = (PFNGLTEXTUREPARAMETERFVPROC) zpl__glgen_get_proc("glTextureParameterfv");
	glgenTextureParameterfvEXT = (PFNGLTEXTUREPARAMETERFVEXTPROC) zpl__glgen_get_proc("glTextureParameterfvEXT");
	glgenTextureParameteri = (PFNGLTEXTUREPARAMETERIPROC) zpl__glgen_get_proc("glTextureParameteri");
	glgenTextureParameteriEXT = (PFNGLTEXTUREPARAMETERIEXTPROC) zpl__glgen_get_proc("glTextureParameteriEXT");
	glgenTextureParameteriv = (PFNGLTEXTUREPARAMETERIVPROC) zpl__glgen_get_proc("glTextureParameteriv");
	glgenTextureParameterivEXT = (PFNGLTEXTUREPARAMETERIVEXTPROC) zpl__glgen_get_proc("glTextureParameterivEXT");
	glgenTextureRenderbufferEXT = (PFNGLTEXTURERENDERBUFFEREXTPROC) zpl__glgen_get_proc("glTextureRenderbufferEXT");
	glgenTextureStorage1D = (PFNGLTEXTURESTORAGE1DPROC) zpl__glgen_get_proc("glTextureStorage1D");
	glgenTextureStorage1DEXT = (PFNGLTEXTURESTORAGE1DEXTPROC) zpl__glgen_get_proc("glTextureStorage1DEXT");
	glgenTextureStorage2D = (PFNGLTEXTURESTORAGE2DPROC) zpl__glgen_get_proc("glTextureStorage2D");
	glgenTextureStorage2DEXT = (PFNGLTEXTURESTORAGE2DEXTPROC) zpl__glgen_get_proc("glTextureStorage2DEXT");
	glgenTextureStorage2DMultisample = (PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC) zpl__glgen_get_proc("glTextureStorage2DMultisample");
	glgenTextureStorage2DMultisampleEXT = (PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC) zpl__glgen_get_proc("glTextureStorage2DMultisampleEXT");
	glgenTextureStorage3D = (PFNGLTEXTURESTORAGE3DPROC) zpl__glgen_get_proc("glTextureStorage3D");
	glgenTextureStorage3DEXT = (PFNGLTEXTURESTORAGE3DEXTPROC) zpl__glgen_get_proc("glTextureStorage3DEXT");
	glgenTextureStorage3DMultisample = (PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC) zpl__glgen_get_proc("glTextureStorage3DMultisample");
	glgenTextureStorage3DMultisampleEXT = (PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC) zpl__glgen_get_proc("glTextureStorage3DMultisampleEXT");
	glgenTextureSubImage1D = (PFNGLTEXTURESUBIMAGE1DPROC) zpl__glgen_get_proc("glTextureSubImage1D");
	glgenTextureSubImage1DEXT = (PFNGLTEXTURESUBIMAGE1DEXTPROC) zpl__glgen_get_proc("glTextureSubImage1DEXT");
	glgenTextureSubImage2D = (PFNGLTEXTURESUBIMAGE2DPROC) zpl__glgen_get_proc("glTextureSubImage2D");
	glgenTextureSubImage2DEXT = (PFNGLTEXTURESUBIMAGE2DEXTPROC) zpl__glgen_get_proc("glTextureSubImage2DEXT");
	glgenTextureSubImage3D = (PFNGLTEXTURESUBIMAGE3DPROC) zpl__glgen_get_proc("glTextureSubImage3D");
	glgenTextureSubImage3DEXT = (PFNGLTEXTURESUBIMAGE3DEXTPROC) zpl__glgen_get_proc("glTextureSubImage3DEXT");
	glgenTextureView = (PFNGLTEXTUREVIEWPROC) zpl__glgen_get_proc("glTextureView");
	glgenTransformFeedbackBufferBase = (PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC) zpl__glgen_get_proc("glTransformFeedbackBufferBase");
	glgenTransformFeedbackBufferRange = (PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC) zpl__glgen_get_proc("glTransformFeedbackBufferRange");
	glgenTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC) zpl__glgen_get_proc("glTransformFeedbackVaryings");
	glgenTransformPathNV = (PFNGLTRANSFORMPATHNVPROC) zpl__glgen_get_proc("glTransformPathNV");
	glgenUniform1d = (PFNGLUNIFORM1DPROC) zpl__glgen_get_proc("glUniform1d");
	glgenUniform1dv = (PFNGLUNIFORM1DVPROC) zpl__glgen_get_proc("glUniform1dv");
	glgenUniform1f = (PFNGLUNIFORM1FPROC) zpl__glgen_get_proc("glUniform1f");
	glgenUniform1fv = (PFNGLUNIFORM1FVPROC) zpl__glgen_get_proc("glUniform1fv");
	glgenUniform1i = (PFNGLUNIFORM1IPROC) zpl__glgen_get_proc("glUniform1i");
	glgenUniform1i64ARB = (PFNGLUNIFORM1I64ARBPROC) zpl__glgen_get_proc("glUniform1i64ARB");
	glgenUniform1i64NV = (PFNGLUNIFORM1I64NVPROC) zpl__glgen_get_proc("glUniform1i64NV");
	glgenUniform1i64vARB = (PFNGLUNIFORM1I64VARBPROC) zpl__glgen_get_proc("glUniform1i64vARB");
	glgenUniform1i64vNV = (PFNGLUNIFORM1I64VNVPROC) zpl__glgen_get_proc("glUniform1i64vNV");
	glgenUniform1iv = (PFNGLUNIFORM1IVPROC) zpl__glgen_get_proc("glUniform1iv");
	glgenUniform1ui = (PFNGLUNIFORM1UIPROC) zpl__glgen_get_proc("glUniform1ui");
	glgenUniform1ui64ARB = (PFNGLUNIFORM1UI64ARBPROC) zpl__glgen_get_proc("glUniform1ui64ARB");
	glgenUniform1ui64NV = (PFNGLUNIFORM1UI64NVPROC) zpl__glgen_get_proc("glUniform1ui64NV");
	glgenUniform1ui64vARB = (PFNGLUNIFORM1UI64VARBPROC) zpl__glgen_get_proc("glUniform1ui64vARB");
	glgenUniform1ui64vNV = (PFNGLUNIFORM1UI64VNVPROC) zpl__glgen_get_proc("glUniform1ui64vNV");
	glgenUniform1uiv = (PFNGLUNIFORM1UIVPROC) zpl__glgen_get_proc("glUniform1uiv");
	glgenUniform2d = (PFNGLUNIFORM2DPROC) zpl__glgen_get_proc("glUniform2d");
	glgenUniform2dv = (PFNGLUNIFORM2DVPROC) zpl__glgen_get_proc("glUniform2dv");
	glgenUniform2f = (PFNGLUNIFORM2FPROC) zpl__glgen_get_proc("glUniform2f");
	glgenUniform2fv = (PFNGLUNIFORM2FVPROC) zpl__glgen_get_proc("glUniform2fv");
	glgenUniform2i = (PFNGLUNIFORM2IPROC) zpl__glgen_get_proc("glUniform2i");
	glgenUniform2i64ARB = (PFNGLUNIFORM2I64ARBPROC) zpl__glgen_get_proc("glUniform2i64ARB");
	glgenUniform2i64NV = (PFNGLUNIFORM2I64NVPROC) zpl__glgen_get_proc("glUniform2i64NV");
	glgenUniform2i64vARB = (PFNGLUNIFORM2I64VARBPROC) zpl__glgen_get_proc("glUniform2i64vARB");
	glgenUniform2i64vNV = (PFNGLUNIFORM2I64VNVPROC) zpl__glgen_get_proc("glUniform2i64vNV");
	glgenUniform2iv = (PFNGLUNIFORM2IVPROC) zpl__glgen_get_proc("glUniform2iv");
	glgenUniform2ui = (PFNGLUNIFORM2UIPROC) zpl__glgen_get_proc("glUniform2ui");
	glgenUniform2ui64ARB = (PFNGLUNIFORM2UI64ARBPROC) zpl__glgen_get_proc("glUniform2ui64ARB");
	glgenUniform2ui64NV = (PFNGLUNIFORM2UI64NVPROC) zpl__glgen_get_proc("glUniform2ui64NV");
	glgenUniform2ui64vARB = (PFNGLUNIFORM2UI64VARBPROC) zpl__glgen_get_proc("glUniform2ui64vARB");
	glgenUniform2ui64vNV = (PFNGLUNIFORM2UI64VNVPROC) zpl__glgen_get_proc("glUniform2ui64vNV");
	glgenUniform2uiv = (PFNGLUNIFORM2UIVPROC) zpl__glgen_get_proc("glUniform2uiv");
	glgenUniform3d = (PFNGLUNIFORM3DPROC) zpl__glgen_get_proc("glUniform3d");
	glgenUniform3dv = (PFNGLUNIFORM3DVPROC) zpl__glgen_get_proc("glUniform3dv");
	glgenUniform3f = (PFNGLUNIFORM3FPROC) zpl__glgen_get_proc("glUniform3f");
	glgenUniform3fv = (PFNGLUNIFORM3FVPROC) zpl__glgen_get_proc("glUniform3fv");
	glgenUniform3i = (PFNGLUNIFORM3IPROC) zpl__glgen_get_proc("glUniform3i");
	glgenUniform3i64ARB = (PFNGLUNIFORM3I64ARBPROC) zpl__glgen_get_proc("glUniform3i64ARB");
	glgenUniform3i64NV = (PFNGLUNIFORM3I64NVPROC) zpl__glgen_get_proc("glUniform3i64NV");
	glgenUniform3i64vARB = (PFNGLUNIFORM3I64VARBPROC) zpl__glgen_get_proc("glUniform3i64vARB");
	glgenUniform3i64vNV = (PFNGLUNIFORM3I64VNVPROC) zpl__glgen_get_proc("glUniform3i64vNV");
	glgenUniform3iv = (PFNGLUNIFORM3IVPROC) zpl__glgen_get_proc("glUniform3iv");
	glgenUniform3ui = (PFNGLUNIFORM3UIPROC) zpl__glgen_get_proc("glUniform3ui");
	glgenUniform3ui64ARB = (PFNGLUNIFORM3UI64ARBPROC) zpl__glgen_get_proc("glUniform3ui64ARB");
	glgenUniform3ui64NV = (PFNGLUNIFORM3UI64NVPROC) zpl__glgen_get_proc("glUniform3ui64NV");
	glgenUniform3ui64vARB = (PFNGLUNIFORM3UI64VARBPROC) zpl__glgen_get_proc("glUniform3ui64vARB");
	glgenUniform3ui64vNV = (PFNGLUNIFORM3UI64VNVPROC) zpl__glgen_get_proc("glUniform3ui64vNV");
	glgenUniform3uiv = (PFNGLUNIFORM3UIVPROC) zpl__glgen_get_proc("glUniform3uiv");
	glgenUniform4d = (PFNGLUNIFORM4DPROC) zpl__glgen_get_proc("glUniform4d");
	glgenUniform4dv = (PFNGLUNIFORM4DVPROC) zpl__glgen_get_proc("glUniform4dv");
	glgenUniform4f = (PFNGLUNIFORM4FPROC) zpl__glgen_get_proc("glUniform4f");
	glgenUniform4fv = (PFNGLUNIFORM4FVPROC) zpl__glgen_get_proc("glUniform4fv");
	glgenUniform4i = (PFNGLUNIFORM4IPROC) zpl__glgen_get_proc("glUniform4i");
	glgenUniform4i64ARB = (PFNGLUNIFORM4I64ARBPROC) zpl__glgen_get_proc("glUniform4i64ARB");
	glgenUniform4i64NV = (PFNGLUNIFORM4I64NVPROC) zpl__glgen_get_proc("glUniform4i64NV");
	glgenUniform4i64vARB = (PFNGLUNIFORM4I64VARBPROC) zpl__glgen_get_proc("glUniform4i64vARB");
	glgenUniform4i64vNV = (PFNGLUNIFORM4I64VNVPROC) zpl__glgen_get_proc("glUniform4i64vNV");
	glgenUniform4iv = (PFNGLUNIFORM4IVPROC) zpl__glgen_get_proc("glUniform4iv");
	glgenUniform4ui = (PFNGLUNIFORM4UIPROC) zpl__glgen_get_proc("glUniform4ui");
	glgenUniform4ui64ARB = (PFNGLUNIFORM4UI64ARBPROC) zpl__glgen_get_proc("glUniform4ui64ARB");
	glgenUniform4ui64NV = (PFNGLUNIFORM4UI64NVPROC) zpl__glgen_get_proc("glUniform4ui64NV");
	glgenUniform4ui64vARB = (PFNGLUNIFORM4UI64VARBPROC) zpl__glgen_get_proc("glUniform4ui64vARB");
	glgenUniform4ui64vNV = (PFNGLUNIFORM4UI64VNVPROC) zpl__glgen_get_proc("glUniform4ui64vNV");
	glgenUniform4uiv = (PFNGLUNIFORM4UIVPROC) zpl__glgen_get_proc("glUniform4uiv");
	glgenUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC) zpl__glgen_get_proc("glUniformBlockBinding");
	glgenUniformHandleui64ARB = (PFNGLUNIFORMHANDLEUI64ARBPROC) zpl__glgen_get_proc("glUniformHandleui64ARB");
	glgenUniformHandleui64NV = (PFNGLUNIFORMHANDLEUI64NVPROC) zpl__glgen_get_proc("glUniformHandleui64NV");
	glgenUniformHandleui64vARB = (PFNGLUNIFORMHANDLEUI64VARBPROC) zpl__glgen_get_proc("glUniformHandleui64vARB");
	glgenUniformHandleui64vNV = (PFNGLUNIFORMHANDLEUI64VNVPROC) zpl__glgen_get_proc("glUniformHandleui64vNV");
	glgenUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC) zpl__glgen_get_proc("glUniformMatrix2dv");
	glgenUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC) zpl__glgen_get_proc("glUniformMatrix2fv");
	glgenUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC) zpl__glgen_get_proc("glUniformMatrix2x3dv");
	glgenUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC) zpl__glgen_get_proc("glUniformMatrix2x3fv");
	glgenUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC) zpl__glgen_get_proc("glUniformMatrix2x4dv");
	glgenUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC) zpl__glgen_get_proc("glUniformMatrix2x4fv");
	glgenUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC) zpl__glgen_get_proc("glUniformMatrix3dv");
	glgenUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC) zpl__glgen_get_proc("glUniformMatrix3fv");
	glgenUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC) zpl__glgen_get_proc("glUniformMatrix3x2dv");
	glgenUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC) zpl__glgen_get_proc("glUniformMatrix3x2fv");
	glgenUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC) zpl__glgen_get_proc("glUniformMatrix3x4dv");
	glgenUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC) zpl__glgen_get_proc("glUniformMatrix3x4fv");
	glgenUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC) zpl__glgen_get_proc("glUniformMatrix4dv");
	glgenUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) zpl__glgen_get_proc("glUniformMatrix4fv");
	glgenUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC) zpl__glgen_get_proc("glUniformMatrix4x2dv");
	glgenUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC) zpl__glgen_get_proc("glUniformMatrix4x2fv");
	glgenUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC) zpl__glgen_get_proc("glUniformMatrix4x3dv");
	glgenUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC) zpl__glgen_get_proc("glUniformMatrix4x3fv");
	glgenUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC) zpl__glgen_get_proc("glUniformSubroutinesuiv");
	glgenUniformui64NV = (PFNGLUNIFORMUI64NVPROC) zpl__glgen_get_proc("glUniformui64NV");
	glgenUniformui64vNV = (PFNGLUNIFORMUI64VNVPROC) zpl__glgen_get_proc("glUniformui64vNV");
	glgenUnmapBuffer = (PFNGLUNMAPBUFFERPROC) zpl__glgen_get_proc("glUnmapBuffer");
	glgenUnmapNamedBuffer = (PFNGLUNMAPNAMEDBUFFERPROC) zpl__glgen_get_proc("glUnmapNamedBuffer");
	glgenUnmapNamedBufferEXT = (PFNGLUNMAPNAMEDBUFFEREXTPROC) zpl__glgen_get_proc("glUnmapNamedBufferEXT");
	glgenUseProgram = (PFNGLUSEPROGRAMPROC) zpl__glgen_get_proc("glUseProgram");
	glgenUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC) zpl__glgen_get_proc("glUseProgramStages");
	glgenUseShaderProgramEXT = (PFNGLUSESHADERPROGRAMEXTPROC) zpl__glgen_get_proc("glUseShaderProgramEXT");
	glgenValidateProgram = (PFNGLVALIDATEPROGRAMPROC) zpl__glgen_get_proc("glValidateProgram");
	glgenValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC) zpl__glgen_get_proc("glValidateProgramPipeline");
	glgenVertexArrayAttribBinding = (PFNGLVERTEXARRAYATTRIBBINDINGPROC) zpl__glgen_get_proc("glVertexArrayAttribBinding");
	glgenVertexArrayAttribFormat = (PFNGLVERTEXARRAYATTRIBFORMATPROC) zpl__glgen_get_proc("glVertexArrayAttribFormat");
	glgenVertexArrayAttribIFormat = (PFNGLVERTEXARRAYATTRIBIFORMATPROC) zpl__glgen_get_proc("glVertexArrayAttribIFormat");
	glgenVertexArrayAttribLFormat = (PFNGLVERTEXARRAYATTRIBLFORMATPROC) zpl__glgen_get_proc("glVertexArrayAttribLFormat");
	glgenVertexArrayBindVertexBufferEXT = (PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC) zpl__glgen_get_proc("glVertexArrayBindVertexBufferEXT");
	glgenVertexArrayBindingDivisor = (PFNGLVERTEXARRAYBINDINGDIVISORPROC) zpl__glgen_get_proc("glVertexArrayBindingDivisor");
	glgenVertexArrayColorOffsetEXT = (PFNGLVERTEXARRAYCOLOROFFSETEXTPROC) zpl__glgen_get_proc("glVertexArrayColorOffsetEXT");
	glgenVertexArrayEdgeFlagOffsetEXT = (PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC) zpl__glgen_get_proc("glVertexArrayEdgeFlagOffsetEXT");
	glgenVertexArrayElementBuffer = (PFNGLVERTEXARRAYELEMENTBUFFERPROC) zpl__glgen_get_proc("glVertexArrayElementBuffer");
	glgenVertexArrayFogCoordOffsetEXT = (PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC) zpl__glgen_get_proc("glVertexArrayFogCoordOffsetEXT");
	glgenVertexArrayIndexOffsetEXT = (PFNGLVERTEXARRAYINDEXOFFSETEXTPROC) zpl__glgen_get_proc("glVertexArrayIndexOffsetEXT");
	glgenVertexArrayMultiTexCoordOffsetEXT = (PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC) zpl__glgen_get_proc("glVertexArrayMultiTexCoordOffsetEXT");
	glgenVertexArrayNormalOffsetEXT = (PFNGLVERTEXARRAYNORMALOFFSETEXTPROC) zpl__glgen_get_proc("glVertexArrayNormalOffsetEXT");
	glgenVertexArraySecondaryColorOffsetEXT = (PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC) zpl__glgen_get_proc("glVertexArraySecondaryColorOffsetEXT");
	glgenVertexArrayTexCoordOffsetEXT = (PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC) zpl__glgen_get_proc("glVertexArrayTexCoordOffsetEXT");
	glgenVertexArrayVertexAttribBindingEXT = (PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC) zpl__glgen_get_proc("glVertexArrayVertexAttribBindingEXT");
	glgenVertexArrayVertexAttribDivisorEXT = (PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC) zpl__glgen_get_proc("glVertexArrayVertexAttribDivisorEXT");
	glgenVertexArrayVertexAttribFormatEXT = (PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC) zpl__glgen_get_proc("glVertexArrayVertexAttribFormatEXT");
	glgenVertexArrayVertexAttribIFormatEXT = (PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC) zpl__glgen_get_proc("glVertexArrayVertexAttribIFormatEXT");
	glgenVertexArrayVertexAttribIOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC) zpl__glgen_get_proc("glVertexArrayVertexAttribIOffsetEXT");
	glgenVertexArrayVertexAttribLFormatEXT = (PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC) zpl__glgen_get_proc("glVertexArrayVertexAttribLFormatEXT");
	glgenVertexArrayVertexAttribLOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC) zpl__glgen_get_proc("glVertexArrayVertexAttribLOffsetEXT");
	glgenVertexArrayVertexAttribOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC) zpl__glgen_get_proc("glVertexArrayVertexAttribOffsetEXT");
	glgenVertexArrayVertexBindingDivisorEXT = (PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC) zpl__glgen_get_proc("glVertexArrayVertexBindingDivisorEXT");
	glgenVertexArrayVertexBuffer = (PFNGLVERTEXARRAYVERTEXBUFFERPROC) zpl__glgen_get_proc("glVertexArrayVertexBuffer");
	glgenVertexArrayVertexBuffers = (PFNGLVERTEXARRAYVERTEXBUFFERSPROC) zpl__glgen_get_proc("glVertexArrayVertexBuffers");
	glgenVertexArrayVertexOffsetEXT = (PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC) zpl__glgen_get_proc("glVertexArrayVertexOffsetEXT");
	glgenVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC) zpl__glgen_get_proc("glVertexAttrib1d");
	glgenVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC) zpl__glgen_get_proc("glVertexAttrib1dv");
	glgenVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC) zpl__glgen_get_proc("glVertexAttrib1f");
	glgenVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC) zpl__glgen_get_proc("glVertexAttrib1fv");
	glgenVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC) zpl__glgen_get_proc("glVertexAttrib1s");
	glgenVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC) zpl__glgen_get_proc("glVertexAttrib1sv");
	glgenVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC) zpl__glgen_get_proc("glVertexAttrib2d");
	glgenVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC) zpl__glgen_get_proc("glVertexAttrib2dv");
	glgenVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC) zpl__glgen_get_proc("glVertexAttrib2f");
	glgenVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC) zpl__glgen_get_proc("glVertexAttrib2fv");
	glgenVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC) zpl__glgen_get_proc("glVertexAttrib2s");
	glgenVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC) zpl__glgen_get_proc("glVertexAttrib2sv");
	glgenVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC) zpl__glgen_get_proc("glVertexAttrib3d");
	glgenVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC) zpl__glgen_get_proc("glVertexAttrib3dv");
	glgenVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC) zpl__glgen_get_proc("glVertexAttrib3f");
	glgenVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC) zpl__glgen_get_proc("glVertexAttrib3fv");
	glgenVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC) zpl__glgen_get_proc("glVertexAttrib3s");
	glgenVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC) zpl__glgen_get_proc("glVertexAttrib3sv");
	glgenVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC) zpl__glgen_get_proc("glVertexAttrib4Nbv");
	glgenVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC) zpl__glgen_get_proc("glVertexAttrib4Niv");
	glgenVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC) zpl__glgen_get_proc("glVertexAttrib4Nsv");
	glgenVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC) zpl__glgen_get_proc("glVertexAttrib4Nub");
	glgenVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC) zpl__glgen_get_proc("glVertexAttrib4Nubv");
	glgenVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC) zpl__glgen_get_proc("glVertexAttrib4Nuiv");
	glgenVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC) zpl__glgen_get_proc("glVertexAttrib4Nusv");
	glgenVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC) zpl__glgen_get_proc("glVertexAttrib4bv");
	glgenVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC) zpl__glgen_get_proc("glVertexAttrib4d");
	glgenVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC) zpl__glgen_get_proc("glVertexAttrib4dv");
	glgenVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC) zpl__glgen_get_proc("glVertexAttrib4f");
	glgenVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC) zpl__glgen_get_proc("glVertexAttrib4fv");
	glgenVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC) zpl__glgen_get_proc("glVertexAttrib4iv");
	glgenVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC) zpl__glgen_get_proc("glVertexAttrib4s");
	glgenVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC) zpl__glgen_get_proc("glVertexAttrib4sv");
	glgenVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC) zpl__glgen_get_proc("glVertexAttrib4ubv");
	glgenVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC) zpl__glgen_get_proc("glVertexAttrib4uiv");
	glgenVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC) zpl__glgen_get_proc("glVertexAttrib4usv");
	glgenVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC) zpl__glgen_get_proc("glVertexAttribBinding");
	glgenVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC) zpl__glgen_get_proc("glVertexAttribDivisor");
	glgenVertexAttribDivisorARB = (PFNGLVERTEXATTRIBDIVISORARBPROC) zpl__glgen_get_proc("glVertexAttribDivisorARB");
	glgenVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC) zpl__glgen_get_proc("glVertexAttribFormat");
	glgenVertexAttribFormatNV = (PFNGLVERTEXATTRIBFORMATNVPROC) zpl__glgen_get_proc("glVertexAttribFormatNV");
	glgenVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC) zpl__glgen_get_proc("glVertexAttribI1i");
	glgenVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC) zpl__glgen_get_proc("glVertexAttribI1iv");
	glgenVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC) zpl__glgen_get_proc("glVertexAttribI1ui");
	glgenVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC) zpl__glgen_get_proc("glVertexAttribI1uiv");
	glgenVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC) zpl__glgen_get_proc("glVertexAttribI2i");
	glgenVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC) zpl__glgen_get_proc("glVertexAttribI2iv");
	glgenVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC) zpl__glgen_get_proc("glVertexAttribI2ui");
	glgenVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC) zpl__glgen_get_proc("glVertexAttribI2uiv");
	glgenVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC) zpl__glgen_get_proc("glVertexAttribI3i");
	glgenVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC) zpl__glgen_get_proc("glVertexAttribI3iv");
	glgenVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC) zpl__glgen_get_proc("glVertexAttribI3ui");
	glgenVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC) zpl__glgen_get_proc("glVertexAttribI3uiv");
	glgenVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC) zpl__glgen_get_proc("glVertexAttribI4bv");
	glgenVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC) zpl__glgen_get_proc("glVertexAttribI4i");
	glgenVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC) zpl__glgen_get_proc("glVertexAttribI4iv");
	glgenVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC) zpl__glgen_get_proc("glVertexAttribI4sv");
	glgenVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC) zpl__glgen_get_proc("glVertexAttribI4ubv");
	glgenVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC) zpl__glgen_get_proc("glVertexAttribI4ui");
	glgenVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC) zpl__glgen_get_proc("glVertexAttribI4uiv");
	glgenVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC) zpl__glgen_get_proc("glVertexAttribI4usv");
	glgenVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC) zpl__glgen_get_proc("glVertexAttribIFormat");
	glgenVertexAttribIFormatNV = (PFNGLVERTEXATTRIBIFORMATNVPROC) zpl__glgen_get_proc("glVertexAttribIFormatNV");
	glgenVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC) zpl__glgen_get_proc("glVertexAttribIPointer");
	glgenVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC) zpl__glgen_get_proc("glVertexAttribL1d");
	glgenVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC) zpl__glgen_get_proc("glVertexAttribL1dv");
	glgenVertexAttribL1i64NV = (PFNGLVERTEXATTRIBL1I64NVPROC) zpl__glgen_get_proc("glVertexAttribL1i64NV");
	glgenVertexAttribL1i64vNV = (PFNGLVERTEXATTRIBL1I64VNVPROC) zpl__glgen_get_proc("glVertexAttribL1i64vNV");
	glgenVertexAttribL1ui64ARB = (PFNGLVERTEXATTRIBL1UI64ARBPROC) zpl__glgen_get_proc("glVertexAttribL1ui64ARB");
	glgenVertexAttribL1ui64NV = (PFNGLVERTEXATTRIBL1UI64NVPROC) zpl__glgen_get_proc("glVertexAttribL1ui64NV");
	glgenVertexAttribL1ui64vARB = (PFNGLVERTEXATTRIBL1UI64VARBPROC) zpl__glgen_get_proc("glVertexAttribL1ui64vARB");
	glgenVertexAttribL1ui64vNV = (PFNGLVERTEXATTRIBL1UI64VNVPROC) zpl__glgen_get_proc("glVertexAttribL1ui64vNV");
	glgenVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC) zpl__glgen_get_proc("glVertexAttribL2d");
	glgenVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC) zpl__glgen_get_proc("glVertexAttribL2dv");
	glgenVertexAttribL2i64NV = (PFNGLVERTEXATTRIBL2I64NVPROC) zpl__glgen_get_proc("glVertexAttribL2i64NV");
	glgenVertexAttribL2i64vNV = (PFNGLVERTEXATTRIBL2I64VNVPROC) zpl__glgen_get_proc("glVertexAttribL2i64vNV");
	glgenVertexAttribL2ui64NV = (PFNGLVERTEXATTRIBL2UI64NVPROC) zpl__glgen_get_proc("glVertexAttribL2ui64NV");
	glgenVertexAttribL2ui64vNV = (PFNGLVERTEXATTRIBL2UI64VNVPROC) zpl__glgen_get_proc("glVertexAttribL2ui64vNV");
	glgenVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC) zpl__glgen_get_proc("glVertexAttribL3d");
	glgenVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC) zpl__glgen_get_proc("glVertexAttribL3dv");
	glgenVertexAttribL3i64NV = (PFNGLVERTEXATTRIBL3I64NVPROC) zpl__glgen_get_proc("glVertexAttribL3i64NV");
	glgenVertexAttribL3i64vNV = (PFNGLVERTEXATTRIBL3I64VNVPROC) zpl__glgen_get_proc("glVertexAttribL3i64vNV");
	glgenVertexAttribL3ui64NV = (PFNGLVERTEXATTRIBL3UI64NVPROC) zpl__glgen_get_proc("glVertexAttribL3ui64NV");
	glgenVertexAttribL3ui64vNV = (PFNGLVERTEXATTRIBL3UI64VNVPROC) zpl__glgen_get_proc("glVertexAttribL3ui64vNV");
	glgenVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC) zpl__glgen_get_proc("glVertexAttribL4d");
	glgenVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC) zpl__glgen_get_proc("glVertexAttribL4dv");
	glgenVertexAttribL4i64NV = (PFNGLVERTEXATTRIBL4I64NVPROC) zpl__glgen_get_proc("glVertexAttribL4i64NV");
	glgenVertexAttribL4i64vNV = (PFNGLVERTEXATTRIBL4I64VNVPROC) zpl__glgen_get_proc("glVertexAttribL4i64vNV");
	glgenVertexAttribL4ui64NV = (PFNGLVERTEXATTRIBL4UI64NVPROC) zpl__glgen_get_proc("glVertexAttribL4ui64NV");
	glgenVertexAttribL4ui64vNV = (PFNGLVERTEXATTRIBL4UI64VNVPROC) zpl__glgen_get_proc("glVertexAttribL4ui64vNV");
	glgenVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC) zpl__glgen_get_proc("glVertexAttribLFormat");
	glgenVertexAttribLFormatNV = (PFNGLVERTEXATTRIBLFORMATNVPROC) zpl__glgen_get_proc("glVertexAttribLFormatNV");
	glgenVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC) zpl__glgen_get_proc("glVertexAttribLPointer");
	glgenVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC) zpl__glgen_get_proc("glVertexAttribP1ui");
	glgenVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC) zpl__glgen_get_proc("glVertexAttribP1uiv");
	glgenVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC) zpl__glgen_get_proc("glVertexAttribP2ui");
	glgenVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC) zpl__glgen_get_proc("glVertexAttribP2uiv");
	glgenVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC) zpl__glgen_get_proc("glVertexAttribP3ui");
	glgenVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC) zpl__glgen_get_proc("glVertexAttribP3uiv");
	glgenVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC) zpl__glgen_get_proc("glVertexAttribP4ui");
	glgenVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC) zpl__glgen_get_proc("glVertexAttribP4uiv");
	glgenVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) zpl__glgen_get_proc("glVertexAttribPointer");
	glgenVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC) zpl__glgen_get_proc("glVertexBindingDivisor");
	glgenVertexFormatNV = (PFNGLVERTEXFORMATNVPROC) zpl__glgen_get_proc("glVertexFormatNV");
	glgenViewport = (PFNGLVIEWPORTPROC) zpl__glgen_get_proc("glViewport");
	glgenViewportArrayv = (PFNGLVIEWPORTARRAYVPROC) zpl__glgen_get_proc("glViewportArrayv");
	glgenViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC) zpl__glgen_get_proc("glViewportIndexedf");
	glgenViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC) zpl__glgen_get_proc("glViewportIndexedfv");
	glgenViewportPositionWScaleNV = (PFNGLVIEWPORTPOSITIONWSCALENVPROC) zpl__glgen_get_proc("glViewportPositionWScaleNV");
	glgenViewportSwizzleNV = (PFNGLVIEWPORTSWIZZLENVPROC) zpl__glgen_get_proc("glViewportSwizzleNV");
	glgenWaitSync = (PFNGLWAITSYNCPROC) zpl__glgen_get_proc("glWaitSync");
	glgenWaitVkSemaphoreNV = (PFNGLWAITVKSEMAPHORENVPROC) zpl__glgen_get_proc("glWaitVkSemaphoreNV");
	glgenWeightPathsNV = (PFNGLWEIGHTPATHSNVPROC) zpl__glgen_get_proc("glWeightPathsNV");
	glgenWindowRectanglesEXT = (PFNGLWINDOWRECTANGLESEXTPROC) zpl__glgen_get_proc("glWindowRectanglesEXT");
}


#endif /* ZPL_GLGEN_IMPLEMENTATION */
