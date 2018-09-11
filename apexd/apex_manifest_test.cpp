/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <gtest/gtest.h>

#include "apex_manifest.h"

namespace android {
namespace apex {

TEST(ApexManifestTest, SimpleTest) {
  auto apexManifest = ApexManifest::Open(
      "{\"name\": \"com.android.example.apex\", \"version\": 1}\n");
  ASSERT_NE(nullptr, apexManifest.get());
  EXPECT_EQ("com.android.example.apex", std::string(apexManifest->GetName()));
  EXPECT_EQ(1, apexManifest->GetVersion());
}

TEST(ApexManifestTest, NameMissing) {
  auto apexManifest = ApexManifest::Open("{\"version\": 1}\n");
  EXPECT_EQ(nullptr, apexManifest.get());
}

TEST(ApexManifestTest, VersionMissing) {
  auto apexManifest =
      ApexManifest::Open("{\"name\": \"com.android.example.apex\"}\n");
  EXPECT_EQ(nullptr, apexManifest.get());
}

TEST(ApexManifestTest, VersionNotNumber) {
  auto apexManifest = ApexManifest::Open(
      "{\"name\": \"com.android.example.apex\", \"version\": \"1\"}\n");
  EXPECT_EQ(nullptr, apexManifest.get());
}

TEST(ApexManifestTest, UnparsableManifest) {
  auto apexManifest = ApexManifest::Open("This is an invalid pony");
  EXPECT_EQ(nullptr, apexManifest.get());
}

}  // namespace apex
}  // namespace android