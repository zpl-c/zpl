// file: zpl_hedley.h

/* Hedley - https://nemequ.github.io/hedley
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 * To the extent possible under law, the author(s) have dedicated all
 * copyright and related and neighboring rights to this software to
 * the public domain worldwide. This software is distributed without
 * any warranty.
 *
 * For details, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 * SPDX-License-Identifier: CC0-1.0
 */

#if !defined(ZPL_HEDLEY_VERSION) || (ZPL_HEDLEY_VERSION < 12)
#if defined(ZPL_HEDLEY_VERSION)
#  undef ZPL_HEDLEY_VERSION
#endif
#define ZPL_HEDLEY_VERSION 12

#if defined(ZPL_STRINGIFY_EX)
#  undef ZPL_STRINGIFY_EX
#endif
#define ZPL_STRINGIFY_EX(x) #x

#if defined(ZPL_STRINGIFY)
#  undef ZPL_STRINGIFY
#endif
#define ZPL_STRINGIFY(x) ZPL_STRINGIFY_EX(x)

#if defined(ZPL_CONCAT_EX)
#  undef ZPL_CONCAT_EX
#endif
#define ZPL_CONCAT_EX(a,b) a##b

#if defined(ZPL_CONCAT)
#  undef ZPL_CONCAT
#endif
#define ZPL_CONCAT(a,b) ZPL_CONCAT_EX(a,b)

#if defined(ZPL_VERSION_ENCODE)
#  undef ZPL_VERSION_ENCODE
#endif
#define ZPL_VERSION_ENCODE(major,minor,patch) (((major) * 1000000) + ((minor) * 1000) + (patch))

#if defined(ZPL_VERSION_DECODE_MAJOR)
#  undef ZPL_VERSION_DECODE_MAJOR
#endif
#define ZPL_VERSION_DECODE_MAJOR(version) ((version) / 1000000)

#if defined(ZPL_VERSION_DECODE_MINOR)
#  undef ZPL_VERSION_DECODE_MINOR
#endif
#define ZPL_VERSION_DECODE_MINOR(version) (((version) % 1000000) / 1000)

#if defined(ZPL_VERSION_DECODE_PATCH)
#  undef ZPL_VERSION_DECODE_PATCH
#endif
#define ZPL_VERSION_DECODE_PATCH(version) ((version) % 1000)

#if defined(ZPL_VERSION_CHECK)
#    undef ZPL_VERSION_CHECK
#endif
#define ZPL_VERSION_CHECK(major,minor,patch) (ZPL_VERSION_ENCODE(major,minor,patch) <= ZPL_VERSION)

#if defined(ZPL_GNUC_VERSION)
#  undef ZPL_GNUC_VERSION
#endif
#if defined(__GNUC__) && defined(__GNUC_PATCHLEVEL__)
#  define ZPL_GNUC_VERSION ZPL_VERSION_ENCODE(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#elif defined(__GNUC__)
#  define ZPL_GNUC_VERSION ZPL_VERSION_ENCODE(__GNUC__, __GNUC_MINOR__, 0)
#endif

#if defined(ZPL_GNUC_VERSION_CHECK)
#  undef ZPL_GNUC_VERSION_CHECK
#endif
#if defined(ZPL_GNUC_VERSION)
#  define ZPL_GNUC_VERSION_CHECK(major,minor,patch) (ZPL_GNUC_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_GNUC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_MSVC_VERSION)
#  undef ZPL_MSVC_VERSION
#endif
#if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 140000000)
#  define ZPL_MSVC_VERSION ZPL_VERSION_ENCODE(_MSC_FULL_VER / 10000000, (_MSC_FULL_VER % 10000000) / 100000, (_MSC_FULL_VER % 100000) / 100)
#elif defined(_MSC_FULL_VER)
#  define ZPL_MSVC_VERSION ZPL_VERSION_ENCODE(_MSC_FULL_VER / 1000000, (_MSC_FULL_VER % 1000000) / 10000, (_MSC_FULL_VER % 10000) / 10)
#elif defined(_MSC_VER)
#  define ZPL_MSVC_VERSION ZPL_VERSION_ENCODE(_MSC_VER / 100, _MSC_VER % 100, 0)
#endif

#if defined(ZPL_MSVC_VERSION_CHECK)
#  undef ZPL_MSVC_VERSION_CHECK
#endif
#if !defined(_MSC_VER)
#  define ZPL_MSVC_VERSION_CHECK(major,minor,patch) (0)
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
#  define ZPL_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_FULL_VER >= ((major * 10000000) + (minor * 100000) + (patch)))
#elif defined(_MSC_VER) && (_MSC_VER >= 1200)
#  define ZPL_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_FULL_VER >= ((major * 1000000) + (minor * 10000) + (patch)))
#else
#  define ZPL_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_VER >= ((major * 100) + (minor)))
#endif

#if defined(ZPL_INTEL_VERSION)
#  undef ZPL_INTEL_VERSION
#endif
#if defined(__INTEL_COMPILER) && defined(__INTEL_COMPILER_UPDATE)
#  define ZPL_INTEL_VERSION ZPL_VERSION_ENCODE(__INTEL_COMPILER / 100, __INTEL_COMPILER % 100, __INTEL_COMPILER_UPDATE)
#elif defined(__INTEL_COMPILER)
#  define ZPL_INTEL_VERSION ZPL_VERSION_ENCODE(__INTEL_COMPILER / 100, __INTEL_COMPILER % 100, 0)
#endif

#if defined(ZPL_INTEL_VERSION_CHECK)
#  undef ZPL_INTEL_VERSION_CHECK
#endif
#if defined(ZPL_INTEL_VERSION)
#  define ZPL_INTEL_VERSION_CHECK(major,minor,patch) (ZPL_INTEL_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_INTEL_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_PGI_VERSION)
#  undef ZPL_PGI_VERSION
#endif
#if defined(__PGI) && defined(__PGIC__) && defined(__PGIC_MINOR__) && defined(__PGIC_PATCHLEVEL__)
#  define ZPL_PGI_VERSION ZPL_VERSION_ENCODE(__PGIC__, __PGIC_MINOR__, __PGIC_PATCHLEVEL__)
#endif

#if defined(ZPL_PGI_VERSION_CHECK)
#  undef ZPL_PGI_VERSION_CHECK
#endif
#if defined(ZPL_PGI_VERSION)
#  define ZPL_PGI_VERSION_CHECK(major,minor,patch) (ZPL_PGI_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_PGI_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_SUNPRO_VERSION)
#  undef ZPL_SUNPRO_VERSION
#endif
#if defined(__SUNPRO_C) && (__SUNPRO_C > 0x1000)
#  define ZPL_SUNPRO_VERSION ZPL_VERSION_ENCODE((((__SUNPRO_C >> 16) & 0xf) * 10) + ((__SUNPRO_C >> 12) & 0xf), (((__SUNPRO_C >> 8) & 0xf) * 10) + ((__SUNPRO_C >> 4) & 0xf), (__SUNPRO_C & 0xf) * 10)
#elif defined(__SUNPRO_C)
#  define ZPL_SUNPRO_VERSION ZPL_VERSION_ENCODE((__SUNPRO_C >> 8) & 0xf, (__SUNPRO_C >> 4) & 0xf, (__SUNPRO_C) & 0xf)
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC > 0x1000)
#  define ZPL_SUNPRO_VERSION ZPL_VERSION_ENCODE((((__SUNPRO_CC >> 16) & 0xf) * 10) + ((__SUNPRO_CC >> 12) & 0xf), (((__SUNPRO_CC >> 8) & 0xf) * 10) + ((__SUNPRO_CC >> 4) & 0xf), (__SUNPRO_CC & 0xf) * 10)
#elif defined(__SUNPRO_CC)
#  define ZPL_SUNPRO_VERSION ZPL_VERSION_ENCODE((__SUNPRO_CC >> 8) & 0xf, (__SUNPRO_CC >> 4) & 0xf, (__SUNPRO_CC) & 0xf)
#endif

#if defined(ZPL_SUNPRO_VERSION_CHECK)
#  undef ZPL_SUNPRO_VERSION_CHECK
#endif
#if defined(ZPL_SUNPRO_VERSION)
#  define ZPL_SUNPRO_VERSION_CHECK(major,minor,patch) (ZPL_SUNPRO_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_SUNPRO_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_EMSCRIPTEN_VERSION)
#  undef ZPL_EMSCRIPTEN_VERSION
#endif
#if defined(__EMSCRIPTEN__)
#  define ZPL_EMSCRIPTEN_VERSION ZPL_VERSION_ENCODE(__EMSCRIPTEN_major__, __EMSCRIPTEN_minor__, __EMSCRIPTEN_tiny__)
#endif

#if defined(ZPL_EMSCRIPTEN_VERSION_CHECK)
#  undef ZPL_EMSCRIPTEN_VERSION_CHECK
#endif
#if defined(ZPL_EMSCRIPTEN_VERSION)
#  define ZPL_EMSCRIPTEN_VERSION_CHECK(major,minor,patch) (ZPL_EMSCRIPTEN_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_EMSCRIPTEN_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_ARM_VERSION)
#  undef ZPL_ARM_VERSION
#endif
#if defined(__CC_ARM) && defined(__ARMCOMPILER_VERSION)
#  define ZPL_ARM_VERSION ZPL_VERSION_ENCODE(__ARMCOMPILER_VERSION / 1000000, (__ARMCOMPILER_VERSION % 1000000) / 10000, (__ARMCOMPILER_VERSION % 10000) / 100)
#elif defined(__CC_ARM) && defined(__ARMCC_VERSION)
#  define ZPL_ARM_VERSION ZPL_VERSION_ENCODE(__ARMCC_VERSION / 1000000, (__ARMCC_VERSION % 1000000) / 10000, (__ARMCC_VERSION % 10000) / 100)
#endif

#if defined(ZPL_ARM_VERSION_CHECK)
#  undef ZPL_ARM_VERSION_CHECK
#endif
#if defined(ZPL_ARM_VERSION)
#  define ZPL_ARM_VERSION_CHECK(major,minor,patch) (ZPL_ARM_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_ARM_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_IBM_VERSION)
#  undef ZPL_IBM_VERSION
#endif
#if defined(__ibmxl__)
#  define ZPL_IBM_VERSION ZPL_VERSION_ENCODE(__ibmxl_version__, __ibmxl_release__, __ibmxl_modification__)
#elif defined(__xlC__) && defined(__xlC_ver__)
#  define ZPL_IBM_VERSION ZPL_VERSION_ENCODE(__xlC__ >> 8, __xlC__ & 0xff, (__xlC_ver__ >> 8) & 0xff)
#elif defined(__xlC__)
#  define ZPL_IBM_VERSION ZPL_VERSION_ENCODE(__xlC__ >> 8, __xlC__ & 0xff, 0)
#endif

#if defined(ZPL_IBM_VERSION_CHECK)
#  undef ZPL_IBM_VERSION_CHECK
#endif
#if defined(ZPL_IBM_VERSION)
#  define ZPL_IBM_VERSION_CHECK(major,minor,patch) (ZPL_IBM_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_IBM_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_TI_VERSION)
#  undef ZPL_TI_VERSION
#endif
#if \
    defined(__TI_COMPILER_VERSION__) && \
    ( \
      defined(__TMS470__) || defined(__TI_ARM__) || \
      defined(__MSP430__) || \
      defined(__TMS320C2000__) \
    )
#  if (__TI_COMPILER_VERSION__ >= 16000000)
#    define ZPL_TI_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#  endif
#endif

#if defined(ZPL_TI_VERSION_CHECK)
#  undef ZPL_TI_VERSION_CHECK
#endif
#if defined(ZPL_TI_VERSION)
#  define ZPL_TI_VERSION_CHECK(major,minor,patch) (ZPL_TI_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_TI_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_TI_CL2000_VERSION)
#  undef ZPL_TI_CL2000_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__TMS320C2000__)
#  define ZPL_TI_CL2000_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(ZPL_TI_CL2000_VERSION_CHECK)
#  undef ZPL_TI_CL2000_VERSION_CHECK
#endif
#if defined(ZPL_TI_CL2000_VERSION)
#  define ZPL_TI_CL2000_VERSION_CHECK(major,minor,patch) (ZPL_TI_CL2000_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_TI_CL2000_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_TI_CL430_VERSION)
#  undef ZPL_TI_CL430_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__MSP430__)
#  define ZPL_TI_CL430_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(ZPL_TI_CL430_VERSION_CHECK)
#  undef ZPL_TI_CL430_VERSION_CHECK
#endif
#if defined(ZPL_TI_CL430_VERSION)
#  define ZPL_TI_CL430_VERSION_CHECK(major,minor,patch) (ZPL_TI_CL430_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_TI_CL430_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_TI_ARMCL_VERSION)
#  undef ZPL_TI_ARMCL_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && (defined(__TMS470__) || defined(__TI_ARM__))
#  define ZPL_TI_ARMCL_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(ZPL_TI_ARMCL_VERSION_CHECK)
#  undef ZPL_TI_ARMCL_VERSION_CHECK
#endif
#if defined(ZPL_TI_ARMCL_VERSION)
#  define ZPL_TI_ARMCL_VERSION_CHECK(major,minor,patch) (ZPL_TI_ARMCL_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_TI_ARMCL_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_TI_CL6X_VERSION)
#  undef ZPL_TI_CL6X_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__TMS320C6X__)
#  define ZPL_TI_CL6X_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(ZPL_TI_CL6X_VERSION_CHECK)
#  undef ZPL_TI_CL6X_VERSION_CHECK
#endif
#if defined(ZPL_TI_CL6X_VERSION)
#  define ZPL_TI_CL6X_VERSION_CHECK(major,minor,patch) (ZPL_TI_CL6X_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_TI_CL6X_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_TI_CL7X_VERSION)
#  undef ZPL_TI_CL7X_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__C7000__)
#  define ZPL_TI_CL7X_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(ZPL_TI_CL7X_VERSION_CHECK)
#  undef ZPL_TI_CL7X_VERSION_CHECK
#endif
#if defined(ZPL_TI_CL7X_VERSION)
#  define ZPL_TI_CL7X_VERSION_CHECK(major,minor,patch) (ZPL_TI_CL7X_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_TI_CL7X_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_TI_CLPRU_VERSION)
#  undef ZPL_TI_CLPRU_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__PRU__)
#  define ZPL_TI_CLPRU_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(ZPL_TI_CLPRU_VERSION_CHECK)
#  undef ZPL_TI_CLPRU_VERSION_CHECK
#endif
#if defined(ZPL_TI_CLPRU_VERSION)
#  define ZPL_TI_CLPRU_VERSION_CHECK(major,minor,patch) (ZPL_TI_CLPRU_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_TI_CLPRU_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_CRAY_VERSION)
#  undef ZPL_CRAY_VERSION
#endif
#if defined(_CRAYC)
#  if defined(_RELEASE_PATCHLEVEL)
#    define ZPL_CRAY_VERSION ZPL_VERSION_ENCODE(_RELEASE_MAJOR, _RELEASE_MINOR, _RELEASE_PATCHLEVEL)
#  else
#    define ZPL_CRAY_VERSION ZPL_VERSION_ENCODE(_RELEASE_MAJOR, _RELEASE_MINOR, 0)
#  endif
#endif

#if defined(ZPL_CRAY_VERSION_CHECK)
#  undef ZPL_CRAY_VERSION_CHECK
#endif
#if defined(ZPL_CRAY_VERSION)
#  define ZPL_CRAY_VERSION_CHECK(major,minor,patch) (ZPL_CRAY_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_CRAY_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_IAR_VERSION)
#  undef ZPL_IAR_VERSION
#endif
#if defined(__IAR_SYSTEMS_ICC__)
#  if __VER__ > 1000
#    define ZPL_IAR_VERSION ZPL_VERSION_ENCODE((__VER__ / 1000000), ((__VER__ / 1000) % 1000), (__VER__ % 1000))
#  else
#    define ZPL_IAR_VERSION ZPL_VERSION_ENCODE(VER / 100, __VER__ % 100, 0)
#  endif
#endif

#if defined(ZPL_IAR_VERSION_CHECK)
#  undef ZPL_IAR_VERSION_CHECK
#endif
#if defined(ZPL_IAR_VERSION)
#  define ZPL_IAR_VERSION_CHECK(major,minor,patch) (ZPL_IAR_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_IAR_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_TINYC_VERSION)
#  undef ZPL_TINYC_VERSION
#endif
#if defined(__TINYC__)
#  define ZPL_TINYC_VERSION ZPL_VERSION_ENCODE(__TINYC__ / 1000, (__TINYC__ / 100) % 10, __TINYC__ % 100)
#endif

#if defined(ZPL_TINYC_VERSION_CHECK)
#  undef ZPL_TINYC_VERSION_CHECK
#endif
#if defined(ZPL_TINYC_VERSION)
#  define ZPL_TINYC_VERSION_CHECK(major,minor,patch) (ZPL_TINYC_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_TINYC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_DMC_VERSION)
#  undef ZPL_DMC_VERSION
#endif
#if defined(__DMC__)
#  define ZPL_DMC_VERSION ZPL_VERSION_ENCODE(__DMC__ >> 8, (__DMC__ >> 4) & 0xf, __DMC__ & 0xf)
#endif

#if defined(ZPL_DMC_VERSION_CHECK)
#  undef ZPL_DMC_VERSION_CHECK
#endif
#if defined(ZPL_DMC_VERSION)
#  define ZPL_DMC_VERSION_CHECK(major,minor,patch) (ZPL_DMC_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_DMC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_COMPCERT_VERSION)
#  undef ZPL_COMPCERT_VERSION
#endif
#if defined(__COMPCERT_VERSION__)
#  define ZPL_COMPCERT_VERSION ZPL_VERSION_ENCODE(__COMPCERT_VERSION__ / 10000, (__COMPCERT_VERSION__ / 100) % 100, __COMPCERT_VERSION__ % 100)
#endif

#if defined(ZPL_COMPCERT_VERSION_CHECK)
#  undef ZPL_COMPCERT_VERSION_CHECK
#endif
#if defined(ZPL_COMPCERT_VERSION)
#  define ZPL_COMPCERT_VERSION_CHECK(major,minor,patch) (ZPL_COMPCERT_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_COMPCERT_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_PELLES_VERSION)
#  undef ZPL_PELLES_VERSION
#endif
#if defined(__POCC__)
#  define ZPL_PELLES_VERSION ZPL_VERSION_ENCODE(__POCC__ / 100, __POCC__ % 100, 0)
#endif

#if defined(ZPL_PELLES_VERSION_CHECK)
#  undef ZPL_PELLES_VERSION_CHECK
#endif
#if defined(ZPL_PELLES_VERSION)
#  define ZPL_PELLES_VERSION_CHECK(major,minor,patch) (ZPL_PELLES_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_PELLES_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_GCC_VERSION)
#  undef ZPL_GCC_VERSION
#endif
#if \
  defined(ZPL_GNUC_VERSION) && \
  !defined(__clang__) && \
  !defined(ZPL_INTEL_VERSION) && \
  !defined(ZPL_PGI_VERSION) && \
  !defined(ZPL_ARM_VERSION) && \
  !defined(ZPL_TI_VERSION) && \
  !defined(ZPL_TI_ARMCL_VERSION) && \
  !defined(ZPL_TI_CL430_VERSION) && \
  !defined(ZPL_TI_CL2000_VERSION) && \
  !defined(ZPL_TI_CL6X_VERSION) && \
  !defined(ZPL_TI_CL7X_VERSION) && \
  !defined(ZPL_TI_CLPRU_VERSION) && \
  !defined(__COMPCERT__)
#  define ZPL_GCC_VERSION ZPL_GNUC_VERSION
#endif

#if defined(ZPL_GCC_VERSION_CHECK)
#  undef ZPL_GCC_VERSION_CHECK
#endif
#if defined(ZPL_GCC_VERSION)
#  define ZPL_GCC_VERSION_CHECK(major,minor,patch) (ZPL_GCC_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
#else
#  define ZPL_GCC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(ZPL_HAS_ATTRIBUTE)
#  undef ZPL_HAS_ATTRIBUTE
#endif
#if defined(__has_attribute)
#  define ZPL_HAS_ATTRIBUTE(attribute) __has_attribute(attribute)
#else
#  define ZPL_HAS_ATTRIBUTE(attribute) (0)
#endif

#if defined(ZPL_GNUC_HAS_ATTRIBUTE)
#  undef ZPL_GNUC_HAS_ATTRIBUTE
#endif
#if defined(__has_attribute)
#  define ZPL_GNUC_HAS_ATTRIBUTE(attribute,major,minor,patch) __has_attribute(attribute)
#else
#  define ZPL_GNUC_HAS_ATTRIBUTE(attribute,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_GCC_HAS_ATTRIBUTE)
#  undef ZPL_GCC_HAS_ATTRIBUTE
#endif
#if defined(__has_attribute)
#  define ZPL_GCC_HAS_ATTRIBUTE(attribute,major,minor,patch) __has_attribute(attribute)
#else
#  define ZPL_GCC_HAS_ATTRIBUTE(attribute,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_HAS_CPP_ATTRIBUTE)
#  undef ZPL_HAS_CPP_ATTRIBUTE
#endif
#if \
  defined(__has_cpp_attribute) && \
  defined(__cplusplus) && \
  (!defined(ZPL_SUNPRO_VERSION) || ZPL_SUNPRO_VERSION_CHECK(5,15,0))
#  define ZPL_HAS_CPP_ATTRIBUTE(attribute) __has_cpp_attribute(attribute)
#else
#  define ZPL_HAS_CPP_ATTRIBUTE(attribute) (0)
#endif

#if defined(ZPL_HAS_CPP_ATTRIBUTE_NS)
#  undef ZPL_HAS_CPP_ATTRIBUTE_NS
#endif
#if !defined(__cplusplus) || !defined(__has_cpp_attribute)
#  define ZPL_HAS_CPP_ATTRIBUTE_NS(ns,attribute) (0)
#elif \
  !defined(ZPL_PGI_VERSION) && \
  !defined(ZPL_IAR_VERSION) && \
  (!defined(ZPL_SUNPRO_VERSION) || ZPL_SUNPRO_VERSION_CHECK(5,15,0)) && \
  (!defined(ZPL_MSVC_VERSION) || ZPL_MSVC_VERSION_CHECK(19,20,0))
#  define ZPL_HAS_CPP_ATTRIBUTE_NS(ns,attribute) ZPL_HAS_CPP_ATTRIBUTE(ns::attribute)
#else
#  define ZPL_HAS_CPP_ATTRIBUTE_NS(ns,attribute) (0)
#endif

#if defined(ZPL_GNUC_HAS_CPP_ATTRIBUTE)
#  undef ZPL_GNUC_HAS_CPP_ATTRIBUTE
#endif
#if defined(__has_cpp_attribute) && defined(__cplusplus)
#  define ZPL_GNUC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) __has_cpp_attribute(attribute)
#else
#  define ZPL_GNUC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_GCC_HAS_CPP_ATTRIBUTE)
#  undef ZPL_GCC_HAS_CPP_ATTRIBUTE
#endif
#if defined(__has_cpp_attribute) && defined(__cplusplus)
#  define ZPL_GCC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) __has_cpp_attribute(attribute)
#else
#  define ZPL_GCC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_HAS_BUILTIN)
#  undef ZPL_HAS_BUILTIN
#endif
#if defined(__has_builtin)
#  define ZPL_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
#  define ZPL_HAS_BUILTIN(builtin) (0)
#endif

#if defined(ZPL_GNUC_HAS_BUILTIN)
#  undef ZPL_GNUC_HAS_BUILTIN
#endif
#if defined(__has_builtin)
#  define ZPL_GNUC_HAS_BUILTIN(builtin,major,minor,patch) __has_builtin(builtin)
#else
#  define ZPL_GNUC_HAS_BUILTIN(builtin,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_GCC_HAS_BUILTIN)
#  undef ZPL_GCC_HAS_BUILTIN
#endif
#if defined(__has_builtin)
#  define ZPL_GCC_HAS_BUILTIN(builtin,major,minor,patch) __has_builtin(builtin)
#else
#  define ZPL_GCC_HAS_BUILTIN(builtin,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_HAS_FEATURE)
#  undef ZPL_HAS_FEATURE
#endif
#if defined(__has_feature)
#  define ZPL_HAS_FEATURE(feature) __has_feature(feature)
#else
#  define ZPL_HAS_FEATURE(feature) (0)
#endif

#if defined(ZPL_GNUC_HAS_FEATURE)
#  undef ZPL_GNUC_HAS_FEATURE
#endif
#if defined(__has_feature)
#  define ZPL_GNUC_HAS_FEATURE(feature,major,minor,patch) __has_feature(feature)
#else
#  define ZPL_GNUC_HAS_FEATURE(feature,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_GCC_HAS_FEATURE)
#  undef ZPL_GCC_HAS_FEATURE
#endif
#if defined(__has_feature)
#  define ZPL_GCC_HAS_FEATURE(feature,major,minor,patch) __has_feature(feature)
#else
#  define ZPL_GCC_HAS_FEATURE(feature,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_HAS_EXTENSION)
#  undef ZPL_HAS_EXTENSION
#endif
#if defined(__has_extension)
#  define ZPL_HAS_EXTENSION(extension) __has_extension(extension)
#else
#  define ZPL_HAS_EXTENSION(extension) (0)
#endif

#if defined(ZPL_GNUC_HAS_EXTENSION)
#  undef ZPL_GNUC_HAS_EXTENSION
#endif
#if defined(__has_extension)
#  define ZPL_GNUC_HAS_EXTENSION(extension,major,minor,patch) __has_extension(extension)
#else
#  define ZPL_GNUC_HAS_EXTENSION(extension,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_GCC_HAS_EXTENSION)
#  undef ZPL_GCC_HAS_EXTENSION
#endif
#if defined(__has_extension)
#  define ZPL_GCC_HAS_EXTENSION(extension,major,minor,patch) __has_extension(extension)
#else
#  define ZPL_GCC_HAS_EXTENSION(extension,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_HAS_DECLSPEC_ATTRIBUTE)
#  undef ZPL_HAS_DECLSPEC_ATTRIBUTE
#endif
#if defined(__has_declspec_attribute)
#  define ZPL_HAS_DECLSPEC_ATTRIBUTE(attribute) __has_declspec_attribute(attribute)
#else
#  define ZPL_HAS_DECLSPEC_ATTRIBUTE(attribute) (0)
#endif

#if defined(ZPL_GNUC_HAS_DECLSPEC_ATTRIBUTE)
#  undef ZPL_GNUC_HAS_DECLSPEC_ATTRIBUTE
#endif
#if defined(__has_declspec_attribute)
#  define ZPL_GNUC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) __has_declspec_attribute(attribute)
#else
#  define ZPL_GNUC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_GCC_HAS_DECLSPEC_ATTRIBUTE)
#  undef ZPL_GCC_HAS_DECLSPEC_ATTRIBUTE
#endif
#if defined(__has_declspec_attribute)
#  define ZPL_GCC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) __has_declspec_attribute(attribute)
#else
#  define ZPL_GCC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_HAS_WARNING)
#  undef ZPL_HAS_WARNING
#endif
#if defined(__has_warning)
#  define ZPL_HAS_WARNING(warning) __has_warning(warning)
#else
#  define ZPL_HAS_WARNING(warning) (0)
#endif

#if defined(ZPL_GNUC_HAS_WARNING)
#  undef ZPL_GNUC_HAS_WARNING
#endif
#if defined(__has_warning)
#  define ZPL_GNUC_HAS_WARNING(warning,major,minor,patch) __has_warning(warning)
#else
#  define ZPL_GNUC_HAS_WARNING(warning,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_GCC_HAS_WARNING)
#  undef ZPL_GCC_HAS_WARNING
#endif
#if defined(__has_warning)
#  define ZPL_GCC_HAS_WARNING(warning,major,minor,patch) __has_warning(warning)
#else
#  define ZPL_GCC_HAS_WARNING(warning,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
#endif

/* ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_ is for
   ZPL INTERNAL USE ONLY.  API subject to change without notice. */
#if defined(ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_)
#  undef ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_
#endif
#if defined(__cplusplus)
#  if ZPL_HAS_WARNING("-Wc++98-compat")
#    if ZPL_HAS_WARNING("-Wc++17-extensions")
#      define ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(xpr) \
         ZPL_DIAGNOSTIC_PUSH \
         _Pragma("clang diagnostic ignored \"-Wc++98-compat\"") \
         _Pragma("clang diagnostic ignored \"-Wc++17-extensions\"") \
         xpr \
         ZPL_DIAGNOSTIC_POP
#    else
#      define ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(xpr) \
         ZPL_DIAGNOSTIC_PUSH \
         _Pragma("clang diagnostic ignored \"-Wc++98-compat\"") \
         xpr \
         ZPL_DIAGNOSTIC_POP
#    endif
#  endif
#endif
#if !defined(ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_)
#  define ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(x) x
#endif

#if defined(ZPL_CONST_CAST)
#  undef ZPL_CONST_CAST
#endif
#if defined(__cplusplus)
#  define ZPL_CONST_CAST(T, expr) (const_cast<T>(expr))
#elif \
  ZPL_HAS_WARNING("-Wcast-qual") || \
  ZPL_GCC_VERSION_CHECK(4,6,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0)
#  define ZPL_CONST_CAST(T, expr) (__extension__ ({ \
      ZPL_DIAGNOSTIC_PUSH \
      ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL \
      ((T) (expr)); \
      ZPL_DIAGNOSTIC_POP \
    }))
#else
#  define ZPL_CONST_CAST(T, expr) ((T) (expr))
#endif

#if defined(ZPL_REINTERPRET_CAST)
#  undef ZPL_REINTERPRET_CAST
#endif
#if defined(__cplusplus)
#  define ZPL_REINTERPRET_CAST(T, expr) (reinterpret_cast<T>(expr))
#else
#  define ZPL_REINTERPRET_CAST(T, expr) ((T) (expr))
#endif

#if defined(ZPL_STATIC_CAST)
#  undef ZPL_STATIC_CAST
#endif
#if defined(__cplusplus)
#  define ZPL_STATIC_CAST(T, expr) (static_cast<T>(expr))
#else
#  define ZPL_STATIC_CAST(T, expr) ((T) (expr))
#endif

#if defined(ZPL_CPP_CAST)
#  undef ZPL_CPP_CAST
#endif
#if defined(__cplusplus)
#  if ZPL_HAS_WARNING("-Wold-style-cast")
#    define ZPL_CPP_CAST(T, expr) \
       ZPL_DIAGNOSTIC_PUSH \
       _Pragma("clang diagnostic ignored \"-Wold-style-cast\"") \
       ((T) (expr)) \
       ZPL_DIAGNOSTIC_POP
#  elif ZPL_IAR_VERSION_CHECK(8,3,0)
#    define ZPL_CPP_CAST(T, expr) \
       ZPL_DIAGNOSTIC_PUSH \
       _Pragma("diag_suppress=Pe137") \
       ZPL_DIAGNOSTIC_POP \
#  else
#    define ZPL_CPP_CAST(T, expr) ((T) (expr))
#  endif
#else
#  define ZPL_CPP_CAST(T, expr) (expr)
#endif

#if \
  (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || \
  defined(__clang__) || \
  ZPL_GCC_VERSION_CHECK(3,0,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_IAR_VERSION_CHECK(8,0,0) || \
  ZPL_PGI_VERSION_CHECK(18,4,0) || \
  ZPL_ARM_VERSION_CHECK(4,1,0) || \
  ZPL_TI_VERSION_CHECK(15,12,0) || \
  ZPL_TI_ARMCL_VERSION_CHECK(4,7,0) || \
  ZPL_TI_CL430_VERSION_CHECK(2,0,1) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,1,0) || \
  ZPL_TI_CL6X_VERSION_CHECK(7,0,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  ZPL_CRAY_VERSION_CHECK(5,0,0) || \
  ZPL_TINYC_VERSION_CHECK(0,9,17) || \
  ZPL_SUNPRO_VERSION_CHECK(8,0,0) || \
  (ZPL_IBM_VERSION_CHECK(10,1,0) && defined(__C99_PRAGMA_OPERATOR))
#  define ZPL_PRAGMA(value) _Pragma(#value)
#elif ZPL_MSVC_VERSION_CHECK(15,0,0)
#  define ZPL_PRAGMA(value) __pragma(value)
#else
#  define ZPL_PRAGMA(value)
#endif

#if defined(ZPL_DIAGNOSTIC_PUSH)
#  undef ZPL_DIAGNOSTIC_PUSH
#endif
#if defined(ZPL_DIAGNOSTIC_POP)
#  undef ZPL_DIAGNOSTIC_POP
#endif
#if defined(__clang__)
#  define ZPL_DIAGNOSTIC_PUSH _Pragma("clang diagnostic push")
#  define ZPL_DIAGNOSTIC_POP _Pragma("clang diagnostic pop")
#elif ZPL_INTEL_VERSION_CHECK(13,0,0)
#  define ZPL_DIAGNOSTIC_PUSH _Pragma("warning(push)")
#  define ZPL_DIAGNOSTIC_POP _Pragma("warning(pop)")
#elif ZPL_GCC_VERSION_CHECK(4,6,0)
#  define ZPL_DIAGNOSTIC_PUSH _Pragma("GCC diagnostic push")
#  define ZPL_DIAGNOSTIC_POP _Pragma("GCC diagnostic pop")
#elif ZPL_MSVC_VERSION_CHECK(15,0,0)
#  define ZPL_DIAGNOSTIC_PUSH __pragma(warning(push))
#  define ZPL_DIAGNOSTIC_POP __pragma(warning(pop))
#elif ZPL_ARM_VERSION_CHECK(5,6,0)
#  define ZPL_DIAGNOSTIC_PUSH _Pragma("push")
#  define ZPL_DIAGNOSTIC_POP _Pragma("pop")
#elif \
    ZPL_TI_VERSION_CHECK(15,12,0) || \
    ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
    ZPL_TI_CL430_VERSION_CHECK(4,4,0) || \
    ZPL_TI_CL6X_VERSION_CHECK(8,1,0) || \
    ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
    ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define ZPL_DIAGNOSTIC_PUSH _Pragma("diag_push")
#  define ZPL_DIAGNOSTIC_POP _Pragma("diag_pop")
#elif ZPL_PELLES_VERSION_CHECK(2,90,0)
#  define ZPL_DIAGNOSTIC_PUSH _Pragma("warning(push)")
#  define ZPL_DIAGNOSTIC_POP _Pragma("warning(pop)")
#else
#  define ZPL_DIAGNOSTIC_PUSH
#  define ZPL_DIAGNOSTIC_POP
#endif

#if defined(ZPL_DIAGNOSTIC_DISABLE_DEPRECATED)
#  undef ZPL_DIAGNOSTIC_DISABLE_DEPRECATED
#endif
#if ZPL_HAS_WARNING("-Wdeprecated-declarations")
#  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#elif ZPL_INTEL_VERSION_CHECK(13,0,0)
#  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("warning(disable:1478 1786)")
#elif ZPL_PGI_VERSION_CHECK(17,10,0)
#  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress 1215,1444")
#elif ZPL_GCC_VERSION_CHECK(4,3,0)
#  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#elif ZPL_MSVC_VERSION_CHECK(15,0,0)
#  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED __pragma(warning(disable:4996))
#elif \
    ZPL_TI_VERSION_CHECK(15,12,0) || \
    (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
    ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
    (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
    ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
    (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
    ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
    (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
    ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
    ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
    ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress 1291,1718")
#elif ZPL_SUNPRO_VERSION_CHECK(5,13,0) && !defined(__cplusplus)
#  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("error_messages(off,E_DEPRECATED_ATT,E_DEPRECATED_ATT_MESS)")
#elif ZPL_SUNPRO_VERSION_CHECK(5,13,0) && defined(__cplusplus)
#  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("error_messages(off,symdeprecated,symdeprecated2)")
#elif ZPL_IAR_VERSION_CHECK(8,0,0)
#  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress=Pe1444,Pe1215")
#elif ZPL_PELLES_VERSION_CHECK(2,90,0)
#  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("warn(disable:2241)")
#else
#  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED
#endif

#if defined(ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS)
#  undef ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS
#endif
#if ZPL_HAS_WARNING("-Wunknown-pragmas")
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("clang diagnostic ignored \"-Wunknown-pragmas\"")
#elif ZPL_INTEL_VERSION_CHECK(13,0,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("warning(disable:161)")
#elif ZPL_PGI_VERSION_CHECK(17,10,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 1675")
#elif ZPL_GCC_VERSION_CHECK(4,3,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("GCC diagnostic ignored \"-Wunknown-pragmas\"")
#elif ZPL_MSVC_VERSION_CHECK(15,0,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS __pragma(warning(disable:4068))
#elif \
    ZPL_TI_VERSION_CHECK(16,9,0) || \
    ZPL_TI_CL6X_VERSION_CHECK(8,0,0) || \
    ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
    ZPL_TI_CLPRU_VERSION_CHECK(2,3,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 163")
#elif ZPL_TI_CL6X_VERSION_CHECK(8,0,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 163")
#elif ZPL_IAR_VERSION_CHECK(8,0,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress=Pe161")
#else
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS
#endif

#if defined(ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES)
#  undef ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES
#endif
#if ZPL_HAS_WARNING("-Wunknown-attributes")
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("clang diagnostic ignored \"-Wunknown-attributes\"")
#elif ZPL_GCC_VERSION_CHECK(4,6,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#elif ZPL_INTEL_VERSION_CHECK(17,0,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("warning(disable:1292)")
#elif ZPL_MSVC_VERSION_CHECK(19,0,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES __pragma(warning(disable:5030))
#elif ZPL_PGI_VERSION_CHECK(17,10,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress 1097")
#elif ZPL_SUNPRO_VERSION_CHECK(5,14,0) && defined(__cplusplus)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("error_messages(off,attrskipunsup)")
#elif \
    ZPL_TI_VERSION_CHECK(18,1,0) || \
    ZPL_TI_CL6X_VERSION_CHECK(8,3,0) || \
    ZPL_TI_CL7X_VERSION_CHECK(1,2,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress 1173")
#elif ZPL_IAR_VERSION_CHECK(8,0,0)
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress=Pe1097")
#else
#  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES
#endif

#if defined(ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL)
#  undef ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL
#endif
#if ZPL_HAS_WARNING("-Wcast-qual")
#  define ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL _Pragma("clang diagnostic ignored \"-Wcast-qual\"")
#elif ZPL_INTEL_VERSION_CHECK(13,0,0)
#  define ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL _Pragma("warning(disable:2203 2331)")
#elif ZPL_GCC_VERSION_CHECK(3,0,0)
#  define ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL _Pragma("GCC diagnostic ignored \"-Wcast-qual\"")
#else
#  define ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL
#endif

#if defined(ZPL_DEPRECATED)
#  undef ZPL_DEPRECATED
#endif
#if defined(ZPL_DEPRECATED_FOR)
#  undef ZPL_DEPRECATED_FOR
#endif
#if defined(__cplusplus) && (__cplusplus >= 201402L)
#  define ZPL_DEPRECATED(since) ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[deprecated("Since " #since)]])
#  define ZPL_DEPRECATED_FOR(since, replacement) ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[deprecated("Since " #since "; use " #replacement)]])
#elif \
  ZPL_HAS_EXTENSION(attribute_deprecated_with_message) || \
  ZPL_GCC_VERSION_CHECK(4,5,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_ARM_VERSION_CHECK(5,6,0) || \
  ZPL_SUNPRO_VERSION_CHECK(5,13,0) || \
  ZPL_PGI_VERSION_CHECK(17,10,0) || \
  ZPL_TI_VERSION_CHECK(18,1,0) || \
  ZPL_TI_ARMCL_VERSION_CHECK(18,1,0) || \
  ZPL_TI_CL6X_VERSION_CHECK(8,3,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,3,0)
#  define ZPL_DEPRECATED(since) __attribute__((__deprecated__("Since " #since)))
#  define ZPL_DEPRECATED_FOR(since, replacement) __attribute__((__deprecated__("Since " #since "; use " #replacement)))
#elif \
  ZPL_HAS_ATTRIBUTE(deprecated) || \
  ZPL_GCC_VERSION_CHECK(3,1,0) || \
  ZPL_ARM_VERSION_CHECK(4,1,0) || \
  ZPL_TI_VERSION_CHECK(15,12,0) || \
  (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define ZPL_DEPRECATED(since) __attribute__((__deprecated__))
#  define ZPL_DEPRECATED_FOR(since, replacement) __attribute__((__deprecated__))
#elif ZPL_MSVC_VERSION_CHECK(14,0,0)
#  define ZPL_DEPRECATED(since) __declspec(deprecated("Since " # since))
#  define ZPL_DEPRECATED_FOR(since, replacement) __declspec(deprecated("Since " #since "; use " #replacement))
#elif \
  ZPL_MSVC_VERSION_CHECK(13,10,0) || \
  ZPL_PELLES_VERSION_CHECK(6,50,0)
#  define ZPL_DEPRECATED(since) __declspec(deprecated)
#  define ZPL_DEPRECATED_FOR(since, replacement) __declspec(deprecated)
#elif ZPL_IAR_VERSION_CHECK(8,0,0)
#  define ZPL_DEPRECATED(since) _Pragma("deprecated")
#  define ZPL_DEPRECATED_FOR(since, replacement) _Pragma("deprecated")
#else
#  define ZPL_DEPRECATED(since)
#  define ZPL_DEPRECATED_FOR(since, replacement)
#endif

#if defined(ZPL_UNAVAILABLE)
#  undef ZPL_UNAVAILABLE
#endif
#if \
  ZPL_HAS_ATTRIBUTE(warning) || \
  ZPL_GCC_VERSION_CHECK(4,3,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0)
#  define ZPL_UNAVAILABLE(available_since) __attribute__((__warning__("Not available until " #available_since)))
#else
#  define ZPL_UNAVAILABLE(available_since)
#endif

#if defined(ZPL_WARN_UNUSED_RESULT)
#  undef ZPL_WARN_UNUSED_RESULT
#endif
#if defined(ZPL_WARN_UNUSED_RESULT_MSG)
#  undef ZPL_WARN_UNUSED_RESULT_MSG
#endif
#if (ZPL_HAS_CPP_ATTRIBUTE(nodiscard) >= 201907L)
#  define ZPL_WARN_UNUSED_RESULT ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard]])
#  define ZPL_WARN_UNUSED_RESULT_MSG(msg) ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard(msg)]])
#elif ZPL_HAS_CPP_ATTRIBUTE(nodiscard)
#  define ZPL_WARN_UNUSED_RESULT ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard]])
#  define ZPL_WARN_UNUSED_RESULT_MSG(msg) ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard]])
#elif \
  ZPL_HAS_ATTRIBUTE(warn_unused_result) || \
  ZPL_GCC_VERSION_CHECK(3,4,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_TI_VERSION_CHECK(15,12,0) || \
  (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  (ZPL_SUNPRO_VERSION_CHECK(5,15,0) && defined(__cplusplus)) || \
  ZPL_PGI_VERSION_CHECK(17,10,0)
#  define ZPL_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#  define ZPL_WARN_UNUSED_RESULT_MSG(msg) __attribute__((__warn_unused_result__))
#elif defined(_Check_return_) /* SAL */
#  define ZPL_WARN_UNUSED_RESULT _Check_return_
#  define ZPL_WARN_UNUSED_RESULT_MSG(msg) _Check_return_
#else
#  define ZPL_WARN_UNUSED_RESULT
#  define ZPL_WARN_UNUSED_RESULT_MSG(msg)
#endif

#if defined(ZPL_SENTINEL)
#  undef ZPL_SENTINEL
#endif
#if \
  ZPL_HAS_ATTRIBUTE(sentinel) || \
  ZPL_GCC_VERSION_CHECK(4,0,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_ARM_VERSION_CHECK(5,4,0)
#  define ZPL_SENTINEL(position) __attribute__((__sentinel__(position)))
#else
#  define ZPL_SENTINEL(position)
#endif

#if defined(ZPL_NO_RETURN)
#  undef ZPL_NO_RETURN
#endif
#if ZPL_IAR_VERSION_CHECK(8,0,0)
#  define ZPL_NO_RETURN __noreturn
#elif ZPL_INTEL_VERSION_CHECK(13,0,0)
#  define ZPL_NO_RETURN __attribute__((__noreturn__))
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#  define ZPL_NO_RETURN _Noreturn
#elif defined(__cplusplus) && (__cplusplus >= 201103L)
#  define ZPL_NO_RETURN ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[noreturn]])
#elif \
  ZPL_HAS_ATTRIBUTE(noreturn) || \
  ZPL_GCC_VERSION_CHECK(3,2,0) || \
  ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
  ZPL_ARM_VERSION_CHECK(4,1,0) || \
  ZPL_IBM_VERSION_CHECK(10,1,0) || \
  ZPL_TI_VERSION_CHECK(15,12,0) || \
  (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define ZPL_NO_RETURN __attribute__((__noreturn__))
#elif ZPL_SUNPRO_VERSION_CHECK(5,10,0)
#  define ZPL_NO_RETURN _Pragma("does_not_return")
#elif ZPL_MSVC_VERSION_CHECK(13,10,0)
#  define ZPL_NO_RETURN __declspec(noreturn)
#elif ZPL_TI_CL6X_VERSION_CHECK(6,0,0) && defined(__cplusplus)
#  define ZPL_NO_RETURN _Pragma("FUNC_NEVER_RETURNS;")
#elif ZPL_COMPCERT_VERSION_CHECK(3,2,0)
#  define ZPL_NO_RETURN __attribute((noreturn))
#elif ZPL_PELLES_VERSION_CHECK(9,0,0)
#  define ZPL_NO_RETURN __declspec(noreturn)
#else
#  define ZPL_NO_RETURN
#endif

#if defined(ZPL_NO_ESCAPE)
#  undef ZPL_NO_ESCAPE
#endif
#if ZPL_HAS_ATTRIBUTE(noescape)
#  define ZPL_NO_ESCAPE __attribute__((__noescape__))
#else
#  define ZPL_NO_ESCAPE
#endif

#if defined(ZPL_UNREACHABLE)
#  undef ZPL_UNREACHABLE
#endif
#if defined(ZPL_UNREACHABLE_RETURN)
#  undef ZPL_UNREACHABLE_RETURN
#endif
#if defined(ZPL_ASSUME)
#  undef ZPL_ASSUME
#endif
#if \
  ZPL_MSVC_VERSION_CHECK(13,10,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0)
#  define ZPL_ASSUME(expr) __assume(expr)
#elif ZPL_HAS_BUILTIN(__builtin_assume)
#  define ZPL_ASSUME(expr) __builtin_assume(expr)
#elif \
    ZPL_TI_CL2000_VERSION_CHECK(6,2,0) || \
    ZPL_TI_CL6X_VERSION_CHECK(4,0,0)
#  if defined(__cplusplus)
#    define ZPL_ASSUME(expr) std::_nassert(expr)
#  else
#    define ZPL_ASSUME(expr) _nassert(expr)
#  endif
#endif
#if \
  (ZPL_HAS_BUILTIN(__builtin_unreachable) && (!defined(ZPL_ARM_VERSION))) || \
  ZPL_GCC_VERSION_CHECK(4,5,0) || \
  ZPL_PGI_VERSION_CHECK(18,10,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_IBM_VERSION_CHECK(13,1,5)
#  define ZPL_UNREACHABLE() __builtin_unreachable()
#elif defined(ZPL_ASSUME)
#  define ZPL_UNREACHABLE() ZPL_ASSUME(0)
#endif
#if !defined(ZPL_ASSUME)
#  if defined(ZPL_UNREACHABLE)
#    define ZPL_ASSUME(expr) ZPL_STATIC_CAST(void, ((expr) ? 1 : (ZPL_UNREACHABLE(), 1)))
#  else
#    define ZPL_ASSUME(expr) ZPL_STATIC_CAST(void, expr)
#  endif
#endif
#if defined(ZPL_UNREACHABLE)
#  if  \
      ZPL_TI_CL2000_VERSION_CHECK(6,2,0) || \
      ZPL_TI_CL6X_VERSION_CHECK(4,0,0)
#    define ZPL_UNREACHABLE_RETURN(value) return (ZPL_STATIC_CAST(void, ZPL_ASSUME(0)), (value))
#  else
#    define ZPL_UNREACHABLE_RETURN(value) ZPL_UNREACHABLE()
#  endif
#else
#  define ZPL_UNREACHABLE_RETURN(value) return (value)
#endif
#if !defined(ZPL_UNREACHABLE)
#  define ZPL_UNREACHABLE() ZPL_ASSUME(0)
#endif

ZPL_DIAGNOSTIC_PUSH
#if ZPL_HAS_WARNING("-Wpedantic")
#  pragma clang diagnostic ignored "-Wpedantic"
#endif
#if ZPL_HAS_WARNING("-Wc++98-compat-pedantic") && defined(__cplusplus)
#  pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#endif
#if ZPL_GCC_HAS_WARNING("-Wvariadic-macros",4,0,0)
#  if defined(__clang__)
#    pragma clang diagnostic ignored "-Wvariadic-macros"
#  elif defined(ZPL_GCC_VERSION)
#    pragma GCC diagnostic ignored "-Wvariadic-macros"
#  endif
#endif
#if defined(ZPL_NON_NULL)
#  undef ZPL_NON_NULL
#endif
#if \
  ZPL_HAS_ATTRIBUTE(nonnull) || \
  ZPL_GCC_VERSION_CHECK(3,3,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_ARM_VERSION_CHECK(4,1,0)
#  define ZPL_NON_NULL(...) __attribute__((__nonnull__(__VA_ARGS__)))
#else
#  define ZPL_NON_NULL(...)
#endif
ZPL_DIAGNOSTIC_POP

#if defined(ZPL_PRINTF_FORMAT)
#  undef ZPL_PRINTF_FORMAT
#endif
#if defined(__MINGW32__) && ZPL_GCC_HAS_ATTRIBUTE(format,4,4,0) && !defined(__USE_MINGW_ANSI_STDIO)
#  define ZPL_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(ms_printf, string_idx, first_to_check)))
#elif defined(__MINGW32__) && ZPL_GCC_HAS_ATTRIBUTE(format,4,4,0) && defined(__USE_MINGW_ANSI_STDIO)
#  define ZPL_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(gnu_printf, string_idx, first_to_check)))
#elif \
  ZPL_HAS_ATTRIBUTE(format) || \
  ZPL_GCC_VERSION_CHECK(3,1,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_ARM_VERSION_CHECK(5,6,0) || \
  ZPL_IBM_VERSION_CHECK(10,1,0) || \
  ZPL_TI_VERSION_CHECK(15,12,0) || \
  (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define ZPL_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(__printf__, string_idx, first_to_check)))
#elif ZPL_PELLES_VERSION_CHECK(6,0,0)
#  define ZPL_PRINTF_FORMAT(string_idx,first_to_check) __declspec(vaformat(printf,string_idx,first_to_check))
#else
#  define ZPL_PRINTF_FORMAT(string_idx,first_to_check)
#endif

#if defined(ZPL_CONSTEXPR)
#  undef ZPL_CONSTEXPR
#endif
#if defined(__cplusplus)
#  if __cplusplus >= 201103L
#    define ZPL_CONSTEXPR ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(constexpr)
#  endif
#endif
#if !defined(ZPL_CONSTEXPR)
#  define ZPL_CONSTEXPR
#endif

#if defined(ZPL_PREDICT)
#  undef ZPL_PREDICT
#endif
#if defined(ZPL_LIKELY)
#  undef ZPL_LIKELY
#endif
#if defined(ZPL_UNLIKELY)
#  undef ZPL_UNLIKELY
#endif
#if defined(ZPL_UNPREDICTABLE)
#  undef ZPL_UNPREDICTABLE
#endif
#if ZPL_HAS_BUILTIN(__builtin_unpredictable)
#  define ZPL_UNPREDICTABLE(expr) __builtin_unpredictable((expr))
#endif
#if \
  ZPL_HAS_BUILTIN(__builtin_expect_with_probability) || \
  ZPL_GCC_VERSION_CHECK(9,0,0)
#  define ZPL_PREDICT(expr, value, probability) __builtin_expect_with_probability(  (expr), (value), (probability))
#  define ZPL_PREDICT_TRUE(expr, probability)   __builtin_expect_with_probability(!!(expr),    1   , (probability))
#  define ZPL_PREDICT_FALSE(expr, probability)  __builtin_expect_with_probability(!!(expr),    0   , (probability))
#  define ZPL_LIKELY(expr)                      __builtin_expect                 (!!(expr),    1                  )
#  define ZPL_UNLIKELY(expr)                    __builtin_expect                 (!!(expr),    0                  )
#elif \
  ZPL_HAS_BUILTIN(__builtin_expect) || \
  ZPL_GCC_VERSION_CHECK(3,0,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  (ZPL_SUNPRO_VERSION_CHECK(5,15,0) && defined(__cplusplus)) || \
  ZPL_ARM_VERSION_CHECK(4,1,0) || \
  ZPL_IBM_VERSION_CHECK(10,1,0) || \
  ZPL_TI_VERSION_CHECK(15,12,0) || \
  ZPL_TI_ARMCL_VERSION_CHECK(4,7,0) || \
  ZPL_TI_CL430_VERSION_CHECK(3,1,0) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,1,0) || \
  ZPL_TI_CL6X_VERSION_CHECK(6,1,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  ZPL_TINYC_VERSION_CHECK(0,9,27) || \
  ZPL_CRAY_VERSION_CHECK(8,1,0)
#  define ZPL_PREDICT(expr, expected, probability) \
     (((probability) >= 0.9) ? __builtin_expect((expr), (expected)) : (ZPL_STATIC_CAST(void, expected), (expr)))
#  define ZPL_PREDICT_TRUE(expr, probability) \
     (__extension__ ({ \
       double zpl_probability_ = (probability); \
       ((zpl_probability_ >= 0.9) ? __builtin_expect(!!(expr), 1) : ((zpl_probability_ <= 0.1) ? __builtin_expect(!!(expr), 0) : !!(expr))); \
     }))
#  define ZPL_PREDICT_FALSE(expr, probability) \
     (__extension__ ({ \
       double zpl_probability_ = (probability); \
       ((zpl_probability_ >= 0.9) ? __builtin_expect(!!(expr), 0) : ((zpl_probability_ <= 0.1) ? __builtin_expect(!!(expr), 1) : !!(expr))); \
     }))
#  define ZPL_LIKELY(expr)   __builtin_expect(!!(expr), 1)
#  define ZPL_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#else
#  define ZPL_PREDICT(expr, expected, probability) (ZPL_STATIC_CAST(void, expected), (expr))
#  define ZPL_PREDICT_TRUE(expr, probability) (!!(expr))
#  define ZPL_PREDICT_FALSE(expr, probability) (!!(expr))
#  define ZPL_LIKELY(expr) (!!(expr))
#  define ZPL_UNLIKELY(expr) (!!(expr))
#endif
#if !defined(ZPL_UNPREDICTABLE)
#  define ZPL_UNPREDICTABLE(expr) ZPL_PREDICT(expr, 1, 0.5)
#endif

#if defined(ZPL_MALLOC)
#  undef ZPL_MALLOC
#endif
#if \
  ZPL_HAS_ATTRIBUTE(malloc) || \
  ZPL_GCC_VERSION_CHECK(3,1,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
  ZPL_ARM_VERSION_CHECK(4,1,0) || \
  ZPL_IBM_VERSION_CHECK(12,1,0) || \
  ZPL_TI_VERSION_CHECK(15,12,0) || \
  (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define ZPL_MALLOC __attribute__((__malloc__))
#elif ZPL_SUNPRO_VERSION_CHECK(5,10,0)
#  define ZPL_MALLOC _Pragma("returns_new_memory")
#elif ZPL_MSVC_VERSION_CHECK(14, 0, 0)
#  define ZPL_MALLOC __declspec(restrict)
#else
#  define ZPL_MALLOC
#endif

#if defined(ZPL_PURE)
#  undef ZPL_PURE
#endif
#if \
  ZPL_HAS_ATTRIBUTE(pure) || \
  ZPL_GCC_VERSION_CHECK(2,96,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
  ZPL_ARM_VERSION_CHECK(4,1,0) || \
  ZPL_IBM_VERSION_CHECK(10,1,0) || \
  ZPL_TI_VERSION_CHECK(15,12,0) || \
  (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  ZPL_PGI_VERSION_CHECK(17,10,0)
#  define ZPL_PURE __attribute__((__pure__))
#elif ZPL_SUNPRO_VERSION_CHECK(5,10,0)
#  define ZPL_PURE _Pragma("does_not_write_global_data")
#elif defined(__cplusplus) && \
    ( \
      ZPL_TI_CL430_VERSION_CHECK(2,0,1) || \
      ZPL_TI_CL6X_VERSION_CHECK(4,0,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) \
    )
#  define ZPL_PURE _Pragma("FUNC_IS_PURE;")
#else
#  define ZPL_PURE
#endif

#if defined(ZPL_CONST)
#  undef ZPL_CONST
#endif
#if \
  ZPL_HAS_ATTRIBUTE(const) || \
  ZPL_GCC_VERSION_CHECK(2,5,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
  ZPL_ARM_VERSION_CHECK(4,1,0) || \
  ZPL_IBM_VERSION_CHECK(10,1,0) || \
  ZPL_TI_VERSION_CHECK(15,12,0) || \
  (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  ZPL_PGI_VERSION_CHECK(17,10,0)
#  define ZPL_CONST __attribute__((__const__))
#elif \
  ZPL_SUNPRO_VERSION_CHECK(5,10,0)
#  define ZPL_CONST _Pragma("no_side_effect")
#else
#  define ZPL_CONST ZPL_PURE
#endif

#if defined(ZPL_RESTRICT)
#  undef ZPL_RESTRICT
#endif
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && !defined(__cplusplus)
#  define ZPL_RESTRICT restrict
#elif \
  ZPL_GCC_VERSION_CHECK(3,1,0) || \
  ZPL_MSVC_VERSION_CHECK(14,0,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_ARM_VERSION_CHECK(4,1,0) || \
  ZPL_IBM_VERSION_CHECK(10,1,0) || \
  ZPL_PGI_VERSION_CHECK(17,10,0) || \
  ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,2,4) || \
  ZPL_TI_CL6X_VERSION_CHECK(8,1,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  (ZPL_SUNPRO_VERSION_CHECK(5,14,0) && defined(__cplusplus)) || \
  ZPL_IAR_VERSION_CHECK(8,0,0) || \
  defined(__clang__)
#  define ZPL_RESTRICT __restrict
#elif ZPL_SUNPRO_VERSION_CHECK(5,3,0) && !defined(__cplusplus)
#  define ZPL_RESTRICT _Restrict
#else
#  define ZPL_RESTRICT
#endif

#if defined(ZPL_INLINE)
#  undef ZPL_INLINE
#endif
#if \
  (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || \
  (defined(__cplusplus) && (__cplusplus >= 199711L))
#  define ZPL_INLINE inline
#elif \
  defined(ZPL_GCC_VERSION) || \
  ZPL_ARM_VERSION_CHECK(6,2,0)
#  define ZPL_INLINE __inline__
#elif \
  ZPL_MSVC_VERSION_CHECK(12,0,0) || \
  ZPL_ARM_VERSION_CHECK(4,1,0) || \
  ZPL_TI_ARMCL_VERSION_CHECK(5,1,0) || \
  ZPL_TI_CL430_VERSION_CHECK(3,1,0) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,2,0) || \
  ZPL_TI_CL6X_VERSION_CHECK(8,0,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define ZPL_INLINE __inline
#else
#  define ZPL_INLINE
#endif

#if defined(ZPL_ALWAYS_INLINE)
#  undef ZPL_ALWAYS_INLINE
#endif
#if \
  ZPL_HAS_ATTRIBUTE(always_inline) || \
  ZPL_GCC_VERSION_CHECK(4,0,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
  ZPL_ARM_VERSION_CHECK(4,1,0) || \
  ZPL_IBM_VERSION_CHECK(10,1,0) || \
  ZPL_TI_VERSION_CHECK(15,12,0) || \
  (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define ZPL_ALWAYS_INLINE __attribute__((__always_inline__)) ZPL_INLINE
#elif ZPL_MSVC_VERSION_CHECK(12,0,0)
#  define ZPL_ALWAYS_INLINE __forceinline
#elif defined(__cplusplus) && \
    ( \
      ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
      ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
      ZPL_TI_CL6X_VERSION_CHECK(6,1,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0) \
    )
#  define ZPL_ALWAYS_INLINE _Pragma("FUNC_ALWAYS_INLINE;")
#elif ZPL_IAR_VERSION_CHECK(8,0,0)
#  define ZPL_ALWAYS_INLINE _Pragma("inline=forced")
#else
#  define ZPL_ALWAYS_INLINE ZPL_INLINE
#endif

#undef ZPL_ALWAYS_INLINE
#define ZPL_ALWAYS_INLINE ZPL_INLINE

#if defined(ZPL_NEVER_INLINE)
#  undef ZPL_NEVER_INLINE
#endif
#if \
  ZPL_HAS_ATTRIBUTE(noinline) || \
  ZPL_GCC_VERSION_CHECK(4,0,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
  ZPL_ARM_VERSION_CHECK(4,1,0) || \
  ZPL_IBM_VERSION_CHECK(10,1,0) || \
  ZPL_TI_VERSION_CHECK(15,12,0) || \
  (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define ZPL_NEVER_INLINE __attribute__((__noinline__))
#elif ZPL_MSVC_VERSION_CHECK(13,10,0)
#  define ZPL_NEVER_INLINE __declspec(noinline)
#elif ZPL_PGI_VERSION_CHECK(10,2,0)
#  define ZPL_NEVER_INLINE _Pragma("noinline")
#elif ZPL_TI_CL6X_VERSION_CHECK(6,0,0) && defined(__cplusplus)
#  define ZPL_NEVER_INLINE _Pragma("FUNC_CANNOT_INLINE;")
#elif ZPL_IAR_VERSION_CHECK(8,0,0)
#  define ZPL_NEVER_INLINE _Pragma("inline=never")
#elif ZPL_COMPCERT_VERSION_CHECK(3,2,0)
#  define ZPL_NEVER_INLINE __attribute((noinline))
#elif ZPL_PELLES_VERSION_CHECK(9,0,0)
#  define ZPL_NEVER_INLINE __declspec(noinline)
#else
#  define ZPL_NEVER_INLINE
#endif

#if defined(ZPL_PRIVATE)
#  undef ZPL_PRIVATE
#endif
#if defined(ZPL_PUBLIC)
#  undef ZPL_PUBLIC
#endif
#if defined(ZPL_IMPORT)
#  undef ZPL_IMPORT
#endif
#if defined(_WIN32) || defined(__CYGWIN__)
#  define ZPL_PRIVATE
#  define ZPL_PUBLIC   __declspec(dllexport)
#  define ZPL_IMPORT   __declspec(dllimport)
#else
#  if \
    ZPL_HAS_ATTRIBUTE(visibility) || \
    ZPL_GCC_VERSION_CHECK(3,3,0) || \
    ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
    ZPL_INTEL_VERSION_CHECK(13,0,0) || \
    ZPL_ARM_VERSION_CHECK(4,1,0) || \
    ZPL_IBM_VERSION_CHECK(13,1,0) || \
    ( \
      defined(__TI_EABI__) && \
      ( \
        (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
        ZPL_TI_CL6X_VERSION_CHECK(7,5,0) \
      ) \
    )
#    define ZPL_PRIVATE __attribute__((__visibility__("hidden")))
#    define ZPL_PUBLIC  __attribute__((__visibility__("default")))
#  else
#    define ZPL_PRIVATE
#    define ZPL_PUBLIC
#  endif
#  define ZPL_IMPORT    extern
#endif

#if defined(ZPL_NO_THROW)
#  undef ZPL_NO_THROW
#endif
#if \
  ZPL_HAS_ATTRIBUTE(nothrow) || \
  ZPL_GCC_VERSION_CHECK(3,3,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0)
#  define ZPL_NO_THROW __attribute__((__nothrow__))
#elif \
  ZPL_MSVC_VERSION_CHECK(13,1,0) || \
  ZPL_ARM_VERSION_CHECK(4,1,0)
#  define ZPL_NO_THROW __declspec(nothrow)
#else
#  define ZPL_NO_THROW
#endif

#if defined(ZPL_FALL_THROUGH)
# undef ZPL_FALL_THROUGH
#endif
#if ZPL_GNUC_HAS_ATTRIBUTE(fallthrough,7,0,0) && !defined(ZPL_PGI_VERSION)
#  define ZPL_FALL_THROUGH __attribute__((__fallthrough__))
#elif ZPL_HAS_CPP_ATTRIBUTE_NS(clang,fallthrough)
#  define ZPL_FALL_THROUGH ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[clang::fallthrough]])
#elif ZPL_HAS_CPP_ATTRIBUTE(fallthrough)
#  define ZPL_FALL_THROUGH ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[fallthrough]])
#elif defined(__fallthrough) /* SAL */
#  define ZPL_FALL_THROUGH __fallthrough
#else
#  define ZPL_FALL_THROUGH
#endif

#if defined(ZPL_RETURNS_NON_NULL)
#  undef ZPL_RETURNS_NON_NULL
#endif
#if \
  ZPL_HAS_ATTRIBUTE(returns_nonnull) || \
  ZPL_GCC_VERSION_CHECK(4,9,0)
#  define ZPL_RETURNS_NON_NULL __attribute__((__returns_nonnull__))
#elif defined(_Ret_notnull_) /* SAL */
#  define ZPL_RETURNS_NON_NULL _Ret_notnull_
#else
#  define ZPL_RETURNS_NON_NULL
#endif

#if defined(ZPL_ARRAY_PARAM)
#  undef ZPL_ARRAY_PARAM
#endif
#if \
  defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && \
  !defined(__STDC_NO_VLA__) && \
  !defined(__cplusplus) && \
  !defined(ZPL_PGI_VERSION) && \
  !defined(ZPL_TINYC_VERSION)
#  define ZPL_ARRAY_PARAM(name) (name)
#else
#  define ZPL_ARRAY_PARAM(name)
#endif

#if defined(ZPL_IS_CONSTANT)
#  undef ZPL_IS_CONSTANT
#endif
#if defined(ZPL_REQUIRE_CONSTEXPR)
#  undef ZPL_REQUIRE_CONSTEXPR
#endif
/* ZPL_IS_CONSTEXPR_ is for
   ZPL INTERNAL USE ONLY.  API subject to change without notice. */
#if defined(ZPL_IS_CONSTEXPR_)
#  undef ZPL_IS_CONSTEXPR_
#endif
#if \
  ZPL_HAS_BUILTIN(__builtin_constant_p) || \
  ZPL_GCC_VERSION_CHECK(3,4,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0) || \
  ZPL_TINYC_VERSION_CHECK(0,9,19) || \
  ZPL_ARM_VERSION_CHECK(4,1,0) || \
  ZPL_IBM_VERSION_CHECK(13,1,0) || \
  ZPL_TI_CL6X_VERSION_CHECK(6,1,0) || \
  (ZPL_SUNPRO_VERSION_CHECK(5,10,0) && !defined(__cplusplus)) || \
  ZPL_CRAY_VERSION_CHECK(8,1,0)
#  define ZPL_IS_CONSTANT(expr) __builtin_constant_p(expr)
#endif
#if !defined(__cplusplus)
#  if \
       ZPL_HAS_BUILTIN(__builtin_types_compatible_p) || \
       ZPL_GCC_VERSION_CHECK(3,4,0) || \
       ZPL_INTEL_VERSION_CHECK(13,0,0) || \
       ZPL_IBM_VERSION_CHECK(13,1,0) || \
       ZPL_CRAY_VERSION_CHECK(8,1,0) || \
       ZPL_ARM_VERSION_CHECK(5,4,0) || \
       ZPL_TINYC_VERSION_CHECK(0,9,24)
#    if defined(__INTPTR_TYPE__)
#      define ZPL_IS_CONSTEXPR_(expr) __builtin_types_compatible_p(__typeof__((1 ? (void*) ((__INTPTR_TYPE__) ((expr) * 0)) : (int*) 0)), int*)
#    else
#      include <stdint.h>
#      define ZPL_IS_CONSTEXPR_(expr) __builtin_types_compatible_p(__typeof__((1 ? (void*) ((intptr_t) ((expr) * 0)) : (int*) 0)), int*)
#    endif
#  elif \
       ( \
          defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && \
          !defined(ZPL_SUNPRO_VERSION) && \
          !defined(ZPL_PGI_VERSION) && \
          !defined(ZPL_IAR_VERSION)) || \
       ZPL_HAS_EXTENSION(c_generic_selections) || \
       ZPL_GCC_VERSION_CHECK(4,9,0) || \
       ZPL_INTEL_VERSION_CHECK(17,0,0) || \
       ZPL_IBM_VERSION_CHECK(12,1,0) || \
       ZPL_ARM_VERSION_CHECK(5,3,0)
#    if defined(__INTPTR_TYPE__)
#      define ZPL_IS_CONSTEXPR_(expr) _Generic((1 ? (void*) ((__INTPTR_TYPE__) ((expr) * 0)) : (int*) 0), int*: 1, void*: 0)
#    else
#      include <stdint.h>
#      define ZPL_IS_CONSTEXPR_(expr) _Generic((1 ? (void*) ((intptr_t) * 0) : (int*) 0), int*: 1, void*: 0)
#    endif
#  elif \
       defined(ZPL_GCC_VERSION) || \
       defined(ZPL_INTEL_VERSION) || \
       defined(ZPL_TINYC_VERSION) || \
       defined(ZPL_TI_ARMCL_VERSION) || \
       ZPL_TI_CL430_VERSION_CHECK(18,12,0) || \
       defined(ZPL_TI_CL2000_VERSION) || \
       defined(ZPL_TI_CL6X_VERSION) || \
       defined(ZPL_TI_CL7X_VERSION) || \
       defined(ZPL_TI_CLPRU_VERSION) || \
       defined(__clang__)
#    define ZPL_IS_CONSTEXPR_(expr) ( \
         sizeof(void) != \
         sizeof(*( \
           1 ? \
             ((void*) ((expr) * 0L) ) : \
             ((struct { char v[sizeof(void) * 2]; } *) 1) \
           ) \
         ) \
       )
#  endif
#endif
#if defined(ZPL_IS_CONSTEXPR_)
#  if !defined(ZPL_IS_CONSTANT)
#    define ZPL_IS_CONSTANT(expr) ZPL_IS_CONSTEXPR_(expr)
#  endif
#  define ZPL_REQUIRE_CONSTEXPR(expr) (ZPL_IS_CONSTEXPR_(expr) ? (expr) : (-1))
#else
#  if !defined(ZPL_IS_CONSTANT)
#    define ZPL_IS_CONSTANT(expr) (0)
#  endif
#  define ZPL_REQUIRE_CONSTEXPR(expr) (expr)
#endif

#if defined(ZPL_BEGIN_C_DECLS)
#  undef ZPL_BEGIN_C_DECLS
#endif
#if defined(ZPL_END_C_DECLS)
#  undef ZPL_END_C_DECLS
#endif
#if defined(ZPL_C_DECL)
#  undef ZPL_C_DECL
#endif
#if defined(__cplusplus)
#  define ZPL_BEGIN_C_DECLS extern "C" {
#  define ZPL_END_C_DECLS }
#  define ZPL_C_DECL extern "C"
#else
#  define ZPL_BEGIN_C_DECLS
#  define ZPL_END_C_DECLS
#  define ZPL_C_DECL
#endif

#if defined(ZPL_STATIC_ASSERT)
#  undef ZPL_STATIC_ASSERT
#endif
#if \
  !defined(__cplusplus) && ( \
      (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)) || \
      ZPL_HAS_FEATURE(c_static_assert) || \
      ZPL_GCC_VERSION_CHECK(6,0,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      defined(_Static_assert) \
    )
#  define ZPL_STATIC_ASSERT(expr, message) _Static_assert(expr, message)
#elif \
  (defined(__cplusplus) && (__cplusplus >= 201103L)) || \
  ZPL_MSVC_VERSION_CHECK(16,0,0)
#  define ZPL_STATIC_ASSERT(expr, message) ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(static_assert(expr, message))
#else
#  define ZPL_STATIC_ASSERT3(cond, msg) typedef char static_assertion_##msg[(!!(cond)) * 2 - 1]
#  define ZPL_STATIC_ASSERT2(cond, line) ZPL_STATIC_ASSERT3(cond, static_assertion_at_line_##line)
#  define ZPL_STATIC_ASSERT1(cond, line) ZPL_STATIC_ASSERT2(cond, line)
#  define ZPL_STATIC_ASSERT(cond, unused) ZPL_STATIC_ASSERT1(cond, __LINE__)
#endif

#if defined(ZPL_NULL)
#  undef ZPL_NULL
#endif
#if defined(__cplusplus)
#  if __cplusplus >= 201103L
#    define ZPL_NULL ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(nullptr)
#  elif defined(NULL)
#    define ZPL_NULL NULL
#  else
#    define ZPL_NULL ZPL_STATIC_CAST(void*, 0)
#  endif
#elif defined(NULL)
#  define ZPL_NULL NULL
#else
#  define ZPL_NULL ((void*) 0)
#endif

#if defined(ZPL_MESSAGE)
#  undef ZPL_MESSAGE
#endif
#if ZPL_HAS_WARNING("-Wunknown-pragmas")
#  define ZPL_MESSAGE(msg) \
  ZPL_DIAGNOSTIC_PUSH \
  ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS \
  ZPL_PRAGMA(message msg) \
  ZPL_DIAGNOSTIC_POP
#elif \
  ZPL_GCC_VERSION_CHECK(4,4,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0)
#  define ZPL_MESSAGE(msg) ZPL_PRAGMA(message msg)
#elif ZPL_CRAY_VERSION_CHECK(5,0,0)
#  define ZPL_MESSAGE(msg) ZPL_PRAGMA(_CRI message msg)
#elif ZPL_IAR_VERSION_CHECK(8,0,0)
#  define ZPL_MESSAGE(msg) ZPL_PRAGMA(message(msg))
#elif ZPL_PELLES_VERSION_CHECK(2,0,0)
#  define ZPL_MESSAGE(msg) ZPL_PRAGMA(message(msg))
#else
#  define ZPL_MESSAGE(msg)
#endif

#if defined(ZPL_WARNING)
#  undef ZPL_WARNING
#endif
#if ZPL_HAS_WARNING("-Wunknown-pragmas")
#  define ZPL_WARNING(msg) \
  ZPL_DIAGNOSTIC_PUSH \
  ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS \
  ZPL_PRAGMA(clang warning msg) \
  ZPL_DIAGNOSTIC_POP
#elif \
  ZPL_GCC_VERSION_CHECK(4,8,0) || \
  ZPL_PGI_VERSION_CHECK(18,4,0) || \
  ZPL_INTEL_VERSION_CHECK(13,0,0)
#  define ZPL_WARNING(msg) ZPL_PRAGMA(GCC warning msg)
#elif ZPL_MSVC_VERSION_CHECK(15,0,0)
#  define ZPL_WARNING(msg) ZPL_PRAGMA(message(msg))
#else
#  define ZPL_WARNING(msg) ZPL_MESSAGE(msg)
#endif

#if defined(ZPL_REQUIRE)
#  undef ZPL_REQUIRE
#endif
#if defined(ZPL_REQUIRE_MSG)
#  undef ZPL_REQUIRE_MSG
#endif
#if ZPL_HAS_ATTRIBUTE(diagnose_if)
#  if ZPL_HAS_WARNING("-Wgcc-compat")
#    define ZPL_REQUIRE(expr) \
       ZPL_DIAGNOSTIC_PUSH \
       _Pragma("clang diagnostic ignored \"-Wgcc-compat\"") \
       __attribute__((diagnose_if(!(expr), #expr, "error"))) \
       ZPL_DIAGNOSTIC_POP
#    define ZPL_REQUIRE_MSG(expr,msg) \
       ZPL_DIAGNOSTIC_PUSH \
       _Pragma("clang diagnostic ignored \"-Wgcc-compat\"") \
       __attribute__((diagnose_if(!(expr), msg, "error"))) \
       ZPL_DIAGNOSTIC_POP
#  else
#    define ZPL_REQUIRE(expr) __attribute__((diagnose_if(!(expr), #expr, "error")))
#    define ZPL_REQUIRE_MSG(expr,msg) __attribute__((diagnose_if(!(expr), msg, "error")))
#  endif
#else
#  define ZPL_REQUIRE(expr)
#  define ZPL_REQUIRE_MSG(expr,msg)
#endif

#if defined(ZPL_FLAGS)
#  undef ZPL_FLAGS
#endif
#if ZPL_HAS_ATTRIBUTE(flag_enum)
#  define ZPL_FLAGS __attribute__((__flag_enum__))
#endif

#if defined(ZPL_FLAGS_CAST)
#  undef ZPL_FLAGS_CAST
#endif
#if ZPL_INTEL_VERSION_CHECK(19,0,0)
#  define ZPL_FLAGS_CAST(T, expr) (__extension__ ({ \
  ZPL_DIAGNOSTIC_PUSH \
      _Pragma("warning(disable:188)") \
      ((T) (expr)); \
      ZPL_DIAGNOSTIC_POP \
    }))
#else
#  define ZPL_FLAGS_CAST(T, expr) ZPL_STATIC_CAST(T, expr)
#endif

#if defined(ZPL_EMPTY_BASES)
#  undef ZPL_EMPTY_BASES
#endif
#if ZPL_MSVC_VERSION_CHECK(19,0,23918) && !ZPL_MSVC_VERSION_CHECK(20,0,0)
#  define ZPL_EMPTY_BASES __declspec(empty_bases)
#else
#  define ZPL_EMPTY_BASES
#endif

/* Remaining macros are deprecated. */

#if defined(ZPL_GCC_NOT_CLANG_VERSION_CHECK)
#  undef ZPL_GCC_NOT_CLANG_VERSION_CHECK
#endif
#if defined(__clang__)
#  define ZPL_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch) (0)
#else
#  define ZPL_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(ZPL_CLANG_HAS_ATTRIBUTE)
#  undef ZPL_CLANG_HAS_ATTRIBUTE
#endif
#define ZPL_CLANG_HAS_ATTRIBUTE(attribute) ZPL_HAS_ATTRIBUTE(attribute)

#if defined(ZPL_CLANG_HAS_CPP_ATTRIBUTE)
#  undef ZPL_CLANG_HAS_CPP_ATTRIBUTE
#endif
#define ZPL_CLANG_HAS_CPP_ATTRIBUTE(attribute) ZPL_HAS_CPP_ATTRIBUTE(attribute)

#if defined(ZPL_CLANG_HAS_BUILTIN)
#  undef ZPL_CLANG_HAS_BUILTIN
#endif
#define ZPL_CLANG_HAS_BUILTIN(builtin) ZPL_HAS_BUILTIN(builtin)

#if defined(ZPL_CLANG_HAS_FEATURE)
#  undef ZPL_CLANG_HAS_FEATURE
#endif
#define ZPL_CLANG_HAS_FEATURE(feature) ZPL_HAS_FEATURE(feature)

#if defined(ZPL_CLANG_HAS_EXTENSION)
#  undef ZPL_CLANG_HAS_EXTENSION
#endif
#define ZPL_CLANG_HAS_EXTENSION(extension) ZPL_HAS_EXTENSION(extension)

#if defined(ZPL_CLANG_HAS_DECLSPEC_DECLSPEC_ATTRIBUTE)
#  undef ZPL_CLANG_HAS_DECLSPEC_DECLSPEC_ATTRIBUTE
#endif
#define ZPL_CLANG_HAS_DECLSPEC_ATTRIBUTE(attribute) ZPL_HAS_DECLSPEC_ATTRIBUTE(attribute)

#if defined(ZPL_CLANG_HAS_WARNING)
#  undef ZPL_CLANG_HAS_WARNING
#endif
#define ZPL_CLANG_HAS_WARNING(warning) ZPL_HAS_WARNING(warning)

#endif /* !defined(ZPL_HEDLEY_VERSION) || (ZPL_HEDLEY_VERSION < X) */

