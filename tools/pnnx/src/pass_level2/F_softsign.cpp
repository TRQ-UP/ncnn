// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "pass_level2.h"

namespace pnnx {

class F_softsign : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
7 6
pnnx.Input              input       0 1 input
prim::Constant          op_0        0 1 8 value=1
prim::Constant          op_1        0 1 7 value=1
aten::abs               op_2        1 1 input 6
aten::add               op_3        3 1 6 7 8 9
aten::div               op_4        2 1 input 9 out
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "F.softsign";
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(F_softsign, 100)

class F_softsign_onnx : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
6 5
pnnx.Input              input       0 1 input
aten::abs               op_0        1 1 input 6
prim::Constant          op_1        0 1 8 value=1
aten::add               op_2        2 1 6 8 9
aten::div               op_3        2 1 input 9 out
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "F.softsign";
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(F_softsign_onnx, 100)

} // namespace pnnx
