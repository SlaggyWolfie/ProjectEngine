#pragma once
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

//#include "GameObject.hpp"
#include "glm.hpp"
#include "Component.hpp"
#include <vector>

namespace Engine
{
	class Game;
	namespace Core
	{
		enum Space { Local, World };
		class Transform : public Component
		{

		public:
			friend class GameObject_;

			Transform();
			virtual ~Transform();

			Transform(const Transform& other);
			Transform& operator=(const Transform& other);


			/**
			 * \brief Sets the transform's world position.
			 * \param position The target world position.
			 */
			void setPosition(const glm::vec3& position);

			/**
			 * \brief Gets the transform's world position.
			 * \return The transform's world position.
			 */
			glm::vec3 getPosition();

			/**
			* \brief Sets the transform's world rotation.
			* \return The target world rotation.
			*/
			void setRotation(const glm::quat& rotation);
			/**
			* \brief Gets the transform's world rotation.
			* \return The transform's world rotation.
			*/
			glm::quat getRotation();

			/**
			* \brief Sets the transform's world scale.
			* \return The target world scale.
			*/
			void setScale(const glm::vec3& scale);
			/**
			* \brief Gets the transform's position.
			* \return The transform's position.
			*/
			glm::vec3 getScale();

			/**
			* \brief Gets the transform's position.
			* \return The transform's position.
			*/
			void setWorldMatrix4X4(const glm::mat4& matrix);
			/**
			* \brief Gets the transform's position.
			* \return The transform's position.
			*/
			glm::mat4 getMatrix4X4();

			//Local

			void setLocalPosition(const glm::vec3& position);
			glm::vec3 getLocalPosition() const;

			void setLocalRotation(const glm::quat& rotation);
			glm::quat getLocalRotation() const;

			void setLocalScale(const glm::vec3& scale);
			glm::vec3 getLocalScale() const;

			void setLocalMatrix4X4(const glm::mat4& matrix);
			glm::mat4 getLocalMatrix4X4();

			glm::mat3 getNormalMatrix();

			glm::vec3 forward();
			glm::vec3 up();
			glm::vec3 right();

			//Operations

			glm::vec3 transformPoint(const glm::vec3& point);
			glm::vec3 inverseTransformPoint(const glm::vec3& point);
			glm::vec3 transformDirection(const glm::vec3& direction);
			glm::vec3 inverseTransformDirection(const glm::vec3& direction);

			void lookAt(Transform* lookAtTarget, const glm::vec3& up = glm::vec3(0, 1, 0));
			void translate(const glm::vec3& translation);
			void rotate(const glm::vec3& axis, float angleRotation, Space relativeSpace = World);
			void rotate(const glm::vec3& eulerAngles, bool useLocalAxes = true, Space space = World);
			void rotateAround(const glm::vec3& axis, float angleRotation, const glm::vec3& point);
			//void rotate(const glm::vec3& eulerAngles, Space space = World);
			void scale(const glm::vec3& scaler);
			void scaleWithPositions(const glm::vec3& scale);

			//Parent/Children
			void setParent(Transform* parent, bool keepWorldTransform = false);
			Transform* getParent() const;
			void makeStatic();
			void unmakeStatic(bool children = true);

			//Transform* addChild(Transform* child, bool keepWorldTransform = false);
			Transform* removeChild(const int& index);
			Transform* removeChild(Transform* child);
			int getChildCount() const;
			Transform* getChild(int index) const;
			Transform** getChildren() const;
			std::vector<Transform*> getChildrenList() const;
			std::vector<Transform*> getChildrenRecursive() const;
		private:
			int _frames = 0;
			Transform * _parent = nullptr;
			std::vector<Transform*> _children;

			glm::vec3 _localPosition = glm::vec3();
			glm::quat _localRotation = glm::quat();
			glm::vec3 _localScale = glm::vec3(1);
			glm::mat4 _localMatrix = glm::mat4(1);

			glm::vec3 _worldPosition = glm::vec3();
			glm::quat _worldRotation = glm::quat();
			glm::vec3 _worldScale = glm::vec3(1);
			glm::mat4 _worldMatrix = glm::mat4(1);
			glm::mat3 _normalMatrix = glm::mat4(1);

			void _makeLocalMatrixDirty();
			void _makeWorldMatrixDirty();
			bool _isLocalMatrixDirty = true;
			bool _isWorldMatrixDirty = true;

			void _determineCaching(Space space);

			glm::mat4 _calculateLocalMatrix() const;
			glm::mat3 _calculateNormalMatrix() const;

			glm::vec3 _calculateWorldPosition();
			glm::quat _calculateWorldRotation();
			glm::vec3 _calculateWorldScale();
			glm::mat4 _calculateWorldMatrix();

			//Convenience
			static glm::vec3 _getTranslation(const glm::mat4& matrix);
			static glm::quat _getOrientation(const glm::mat4& matrix);
			static glm::vec3 _getScale(const glm::mat4& matrix);
			static glm::vec3 _getSkew(const glm::mat4& matrix);
			static glm::vec4 _getPerspective(const glm::mat4& matrix);
			static void _getTRS(const glm::mat4& matrix, glm::vec3& position, glm::quat& rotation, glm::vec3& scale);

			glm::vec4 _transformVector(glm::vec4 vector);
			glm::vec4 _inverseTransformVector(glm::vec4 vector);

			glm::vec3 _getLocalSpaceDirection(const glm::vec3& direction);

			Game* _game = nullptr;

		protected:
			bool isUniquePerGameObject() override;
			void destroy() override;
			void prewake() override;
			//void fixedUpdate() override;
			void update() override;
		};
	}
}
#endif //TRANSFORM_HPP